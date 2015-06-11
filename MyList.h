#pragma once
#include<iostream>
using namespace std;

template <class T>
class MyList {
public:
	// standard cout for MyList.
	friend ostream & operator<<(ostream &os, const MyList &obj){
		os<<"[";
		for(int i = 0; i <= obj.len - 2; ++i)
		{
			os<<obj.a[i]<<", ";
		}
		os<<obj.a[obj.len-1]<<"]";
		return os;
	}
	
	// add a new MyList to the end of a MyList.
	friend MyList operator + (const MyList &l1, const MyList &l2){
		MyList newList(l1);
		for(int i = 0; i < l2.len; ++i){
			newList.push(l2.a[i]);
		}
		return newList;
	}

	// add a new elment to the end of a MyList.
	friend MyList operator + (const MyList &l1, const T &item){
		MyList newList(l1);
		newList.push(item);
		return newList;
	}

private:

	T *a;
	int size;
	// the real size of the MyList obj.
	int len;

	// when the size of list is not enough for MyList, do this function.
	void double_space(){
		size *= 2; 
		T *b = new T[size];
		for(int i = 0; i < len; ++i){
			b[i] = a[i];
		}
		delete [] a;
		a = b;
	}

	// quick sort -- from small ones to big ones.
	void quick_sort(int a[], int l, int r){
		if(l < r){
			int x = a[l];
			int i = l, j = r;
			while (i < j){
				while(i < j && a[j] >= x) --j;
				if(i < j){
					a[i] = a[j];
					++i;
				}
				while(i < j && a[i] < x) ++i;
				if(i < j){
					a[j] = a[i];
					--j;
				}
			}
			a[i] = x;
			quick_sort(a, l, i - 1);
			quick_sort(a, i + 1, r);
		}
	}
	
	// quick sort -- from big ones to small ones.
	void quick_sort_r(int a[], int l, int r){
		if(l < r){
			int x = a[l];
			int i = l, j = r;
			while (i < j){
				while(i < j && a[j] <= x) --j;
				if(i < j){
					a[i] = a[j];
					++i;
				}
				while(i < j && a[i] > x) ++i;
				if(i < j){
					a[j] = a[i];
					--j;
				}
			}
			a[i] = x;
			quick_sort(a, l, i - 1);
			quick_sort(a, i + 1, r);
		}
	}
	
public:

	// nonparametric constructor.
	MyList(){
		size = 100;
		len = 0;
		a = new T[size];
	}

	// use num items to fill the MyList.
	MyList(int num, const T &item){
		size = num;
		len = num;
		a = new T[size];
		for(int i = 0; i < len; ++i){
				a[i] = item;
		}
	}

	// Make a MyList in corresponding to MyList l.
	MyList(const MyList &l){
		size = l.size;
		len = l.len;
		a = new T[size];
		for(int i = 0; i < len; ++i){
			a[i] = l.a[i];
		}
	}

	// Make a MyList by the first l elements of arr[].
	MyList(T* arr, int l){
		len = l;
		size = l;
		a = new T[size];
		for(int i = 0; i < len; ++i){
			a[i] = arr[i];
		}
	}

	// add a item to the end of MyList.
	void push(const T &item){
		++len;
		if(len > size){
			double_space();
		}
		a[len - 1] = item;
	}

	// pop the last item.
	T pop(){
		try{
			if(len == 0){
				throw 0;
			}
			else{
				--len;
				return a[len - 1];
			}
		}
		catch(int condition){
			if(condition == 0){
				cout<<"no element"<<endl;
			}
		}
	}

	// insert a item in front of the index item of the MyList.
	void insert(int index, const T &item){
		++len;
		if(len > size){
			double_space();
		}
		for(int i = len - 1; i > index; --i){
			a[i] = a[i - 1];
		}
		a[index] = item;
	}
	
	// clean a MyList object.
	void clean(){
		size = 100;
		len = 0;
		T *b = new T[size];
		delete [] a;
		a = b;
	}

	// get the real size of MyList object.
	int get_size(){
		return len;
	}

	// delete the item from start to end(include).
	void erase(int start, int end)
	{
		if(start < 0) start = len + start;
		if(end < 0) end = len + end;
		try{
			if(start > len - 1 || start < 0){
				throw 0;
			}
			if(end > len - 1 || end < 0){
				throw 1;
			}
			if(start <= end){
				int ers = end - start + 1;
				for(int i = start; i < len - ers; ++i){
					a[i] = a[i + ers];
				}
				len -= ers;
			}
		}
		catch(int condition) {
			if(condition == 0) {cout<<"wrong start point"<<endl;}
			if(condition == 1) {cout<<"wrong start point"<<endl;}
		}
	}
	
	// get the index(th) item of the MyList obj.
	T get_item(int index){
		if(index < 0) index = len + index;
		try {
			if(index < 0 || index > len - 1) {
				throw 0;
			}
			else {
				return a[index];
			}
		}
		catch(int condition) {
			if(condition == 0) {
				cout<<"index out of range"<<endl;
			}
		}
	}

	// return a new MyList obj including the item from start to end. 
	MyList get_item(int start, int end){
		MyList me;
		if(start < 0) start = len + start;
		if(end < 0) end = len + end;
		if(start > end){
			return me;
		}
		try{
			if(start > len - 1 || start < 0){
				throw 0;
			}
			if(end > len - 1 || end < 0){
				throw 1;
			}
			if(start <= end){
				for(int i = start; i <= end; ++i){
					me.push(a[i]);
				}
				return me;
			}
		}
		catch (int condition) {
			if(condition == 0){
				cout<<"wrong start point"<<endl;
			}
			if(condition == 1){
				cout<<"wrong end point"<<endl;
			}
			return me;
		}
	}

	// find the location of the item.
	int count(const T &item){
		int cnt = 0;
		for(int i = 0; i < len; ++i){
			if(a[i] == item){
				++cnt;
			}
		}
		return cnt;
	}
	
	// remove the item in MyList obj.
	void remove(const T &item){
		for(int i = 0; i < len; ++i){
			if(a[i] == item){
				erase(i, i);
				break;
			}
		}
	}

	// assign a obj to another obj.
	MyList &operator = (const MyList &l){
		if(&l == this) return *this;
		size = l.size;
		len = l.len;
		a = new T[size];
		for(int i = 0; i < len; ++i){
			a[i] = l.a[i];
		}
	}

	// add a item to the end of the MyList obj.
	MyList &operator += (const T &item){
		++len;
		if(len > size){
			double_space();
		}
		a[len - 1] = item;
		return *this;
	}

	// add a obj to the end of the obj.
	MyList &operator += (const MyList &l){
		for(int i = 0; i < l.len; ++i){
			this->push(l.a[i]);
		}
		return *this;
	}

	// return the index(th) item of the obj.
	T &operator [](int index){
		if(index < 0) index = len + index;
		try {
			if(index < 0 || index > len - 1) {
				throw 0;
			}
			else {
				return a[index];
			}
		}
		catch(int condition) {
			if(condition == 0) {
				cout<<"index out of range"<<endl;
			}
		}
	}

	// sort, true means from small to big.
	void sort(bool less=true){
		if(less) quick_sort(a, 0, len - 1);
		else quick_sort_r(a, 0, len - 1);
	}

	// reverse the elements.
	void reverse(){
		T *b = new T[size];
		for(int i = 0; i < len; ++i){
			b[len - i - 1] = a[i];
		}
		delete [] a;
		a = b;
	}
	
	// destructor
	~MyList(void){delete [] a;}
};
