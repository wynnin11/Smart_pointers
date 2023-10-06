#include <iostream>
#include <cstdlib>
#include <cassert>
#include <memory>
using namespace std;
template<class T>
class smart_ptr{
private:
T* ptr;
public:
    smart_ptr(){
        ptr = NULL;
    }
    smart_ptr(T* x ){
        ptr = x;
    }
    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }
    smart_ptr(const T& rhs){
        *ptr = rhs;
    }
    ~smart_ptr(){
        delete ptr;
    }
};
template<class T>
class SA{
private:
 int low, high;
 T* p;
//    unique_ptr p;
public:
  // default constructor
  // allows for writing things like SA a;
   SA(){low=0; high=-1;p=NULL;}

    //Constructor taking a uniform initializer list
    SA(initializer_list<T> l){
        low = 0;
        high = l.size() - 1;
        p = new T[l.size()];
        int i=0;
        for(auto k:l)
        p[i++] = k;
    }
    
   // 2 parameter constructor lets us write
    // SA x(10,20);
    SA(int l, int h) {
       if((h-l+1)<=0){
         cout<< "constructor error in bounds definition"<<endl;
         exit(1);
       }
       low=l;
       high=h;
       p = new T[h-l+1];
    }
    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9
    SA(int i){
      low=0; high=i-1;
      p = new T[i];
    }
    // copy constructor for pass by value and
    // initialization
    SA(const SA & s){
       int size=s.high-s.low+1;
       p = new T[size];
       for(int i=0; i<size; i++){
         p[i]=s.p[i];
       }
       low=s.low;
       high=s.high;
    }
    // destructor

    ~SA(){
      delete [] p;
    }
    //overloaded [] lets us write
 //SA x(10,20); x[15]= 100;

    T& operator[](int i){
      if(i < low || i > high){
        cout<< "index "<<i<<" out of range"<<endl;
        exit(1);
      }
      return p[i-low];
    }
    // overloaded assignment lets us assign
    // one SA to another

    SA & operator=(const SA & s){
      if(this==&s)return *this;
      delete [] p;
      int size=s.high-s.low+1;
      p = new T[size];
      for(int i=0; i<size; i++){
        p[i]=s.p[i];
      }
      low=s.low;
      high=s.high;
      return *this;
    }

    // overloads << so we can directly print SAs
    friend ostream& operator<<(ostream& os, SA s){
      int size=s.high-s.low+1;
      for(int i=0; i<size; i++){
        cout<<s.p[i]<<endl;
      }
      return os;
    }
};

int main(){
    SA z {10,20,30};
    cout<<z[2]<<endl;
    
    //SA v(1,3){1,2,3};
    //This does work as the act of first calling the SA constructor doesnt return any type,
    //For the SA object initializates the size SA the uniform initialization brackets call is unable to do anything

    //2. Change the internal pointer to a sma(rt pointer.
    smart_ptr ptr = new smart_ptr<SA<int>>(z);
    //ptr->p[2];
}
