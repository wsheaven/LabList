/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once
#include <cassert>     // for ASSERT
#include <iostream>    // for nullptr
#include <new>         // std::bad_alloc
#include <memory>      // for std::allocator
 
class TestList;        // forward declaration for unit tests
class TestHash;        // to be used later

namespace custom
{

/**************************************************
 * LIST
 * Just like std::list
 **************************************************/
template <typename T>
class list
{
   friend class ::TestList; // give unit tests access to the privates
   friend class ::TestHash;
   friend void swap(list& lhs, list& rhs);
public:  
   // 
   // Construct
   //

   list();
   list(list <T> & rhs);
   list(list <T>&& rhs);
   list(size_t num, const T & t);
   list(size_t num);
   list(const std::initializer_list<T>& il);
   template <class Iterator>
   list(Iterator first, Iterator last);
  ~list() 
   {
   }

   // 
   // Assign
   //

   list <T> & operator = (list &  rhs);
   list <T> & operator = (list && rhs);
   list <T> & operator = (const std::initializer_list<T>& il);
   void swap(list <T>& rhs);

   //
   // Iterator
   //

   class  iterator;
   iterator begin()  { return iterator(); }
   iterator rbegin() { return iterator(); }
   iterator end()    { return iterator(); }

   //
   // Access
   //

   T& front();
   T& back();

   //
   // Insert
   //

   void push_front(const T&  data);
   void push_front(      T&& data);
   void push_back (const T&  data);
   void push_back (      T&& data);
   iterator insert(iterator it, const T& data);
   iterator insert(iterator it, T&& data);

   //
   // Remove
   //

   void pop_back();
   void pop_front();
   void clear();
   iterator erase(const iterator& it);

   // 
   // Status
   //

   bool empty()  const { return pHead == NULL; }
   size_t size() const { return numElements;   }


private:
   // nested linked list class
   class Node;

   // member variables
   size_t numElements; // though we could count, it is faster to keep a variable
   Node * pHead;    // pointer to the beginning of the list
   Node * pTail;    // pointer to the ending of the list
};

 /*************************************************
  * NODE
  * the node class.  Since we do not validate any
  * of the setters, there is no point in making them
  * private.  This is the case because only the
  * List class can make validation decisions
  *************************************************/
template <class T>
class list <T>::Node
{
public:

   //
   // Construct
   //

   Node()
   {
      pPrev = pNext = nullptr;
   }
   Node(const T& data) : data(data), pPrev(nullptr), pNext(nullptr)
   {

   }
   Node(T&& data)
   {
      this->data = std::move(data);
      pPrev = pNext = nullptr;
   }

   //
   // Member variables
   //

   T data;                 // user data
   list <T>::Node* pNext;       // pointer to next node
   list <T>::Node* pPrev;       // pointer to previous node
};

/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
template <typename T>
class list <T> :: iterator
{
   friend class ::TestList; // give unit tests access to the privates
   friend class ::TestHash;
   template <typename TT>
   friend class custom::list;
public:
   // constructors, destructors, and assignment operator
   iterator() 
   {
      p = new typename list <T> ::Node;
   }
   iterator(Node * p) 
   {
      p = new typename list <T> ::Node;
   }
   iterator(const iterator  & rhs) 
   {
      p = new typename list <T> ::Node;
   }
   iterator & operator = (const iterator & rhs)
   {
      return *this;
   }
   
   // equals, not equals operator
   bool operator == (const iterator & rhs) const { return true; }
   bool operator != (const iterator & rhs) const { return true; }

   // dereference operator, fetch a node
   T & operator * ()
   {
      return *(new T);
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      return *this;
   }

   // prefix increment
   iterator & operator ++ ()
   {
      return *this;
   }
   
   // postfix decrement
   iterator operator -- (int postfix)
   {
      return *this;
   }

   // prefix decrement
   iterator & operator -- ()
   {
      return *this;
   } 

   // two friends who need to access p directly
   friend iterator list <T> :: insert(iterator it, const T &  data);
   friend iterator list <T> :: insert(iterator it,       T && data);
   friend iterator list <T> :: erase(const iterator & it);

private:

   typename list <T> :: Node * p;
};

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num, const T & t) 
{
   numElements = num;
   pHead = pTail = new list <T> ::Node(t);
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> ::list(const std::initializer_list<T>& il)
{
   pHead = nullptr;
   pTail = nullptr;
   for (int num : il) {
      push_back(num);
   }
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num)
{
   pHead = pTail = new list <T> ::Node(num); 
   numElements = 1;
}

/*****************************************
 * LIST :: DEFAULT constructors
 ****************************************/
template <typename T>
list <T> ::list() 
{
   numElements = 0;
   pHead = pTail = nullptr;
}

/*****************************************
 * LIST :: COPY constructors
 ****************************************/
template <typename T>
list <T> ::list(list& rhs) 
{
   pHead = nullptr;
   pTail = nullptr;
   for (list <T> ::Node* i = pHead; i != nullptr; i = i->pNext)
   {
      push_back(i->data);
   }
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
template <typename T>
list <T> ::list(list <T>&& rhs)
{
   this->numElements = rhs.numElements;
   this->pHead = rhs.pHead;
   this->pTail = rhs.pTail;

   rhs.pHead = nullptr;
   rhs.pTail = nullptr;
   rhs.numElements = 0;
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS 
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (list <T> && rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T> & list <T> :: operator = (list <T> & rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (const std::initializer_list<T>& rhs)
{
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
void list <T> :: clear()
{
   while (this->pHead != nullptr)
   {
      pop_back();
   }
}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_back(const T & data)
{
   list <T> ::Node* newNode = new list <T> ::Node(data);
   newNode->pNext = nullptr;
   newNode->pPrev = pTail;
   if(pTail != nullptr)
      pTail->pNext = newNode;
   pTail = newNode;
   numElements++;
}

template <typename T>
void list <T> ::push_back(T && data)
{
   list <T> ::Node* newNode = new list <T> ::Node(std::move(data));
   newNode->pNext = nullptr;
   newNode->pPrev = pTail;
   if (pTail != nullptr)
      pTail->pNext = newNode;
   pTail = newNode;
   numElements++;
}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_front(const T & data)
{
   list <T> ::Node* newNode = new list <T> ::Node(data);
   newNode->pNext = pHead;
   newNode->pPrev = nullptr;
   if (pHead != nullptr)
      pHead->pPrev = newNode;
   pHead = newNode;
   numElements++;

}

template <typename T>
void list <T> ::push_front(T && data)
{
   list <T> ::Node* newNode = new list <T> ::Node(std::move(data));
   newNode->pNext = pHead;
   newNode->pPrev = nullptr;
   if (pHead != nullptr)
      pHead->pPrev = newNode;
   pHead = newNode;
   numElements++;
}


/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  : 
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_back()
{
   if (pTail == nullptr) {
      return;
   }

   if (pTail->pPrev != nullptr) {
      pTail->pPrev->pNext = nullptr;
   }
   else {
      pHead = nullptr;
   }

   delete pTail;
   pTail = pTail->pPrev;
   numElements--;
}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_front()
{
   if (pHead == nullptr) {
      return;
   }

   if (pHead->pNext != nullptr) {
      pHead->pNext->pPrev = nullptr;
   }
   else {
      pTail = nullptr;
   }

   list<T>::Node* temp = pHead;
   pHead = pHead->pNext;

   delete temp;
   numElements--;
}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: front()
{
   if(pHead != nullptr)
      return pHead->data;
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: back()
{
   if (pTail != nullptr)
      return pTail->data;
}

/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location 
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator  list <T> :: erase(const list <T> :: iterator & it)
{
   return end();
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
                                                 const T & data) 
{
   return end();
}

template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
   T && data)
{
   return end();
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
template <typename T>
void swap(list <T> & lhs, list <T> & rhs)
{
   list <T> ::Node* tempHead = rhs.pHead;
   rhs.pHead = lhs.pHead;
   lhs.pHead = tempHead;

   list <T> ::Node* tempTail = rhs.pTail;
   rhs.pTail = lhs.pTail;
   lhs.pTail = tempTail;

   int tempElements = rhs.numElements;
   rhs.numElements = lhs.numElements;
   lhs.numElements = tempElements;
}

template <typename T>
void list<T>::swap(list <T>& rhs)
{
   list <T> ::Node* tempHead = rhs.pHead;
   rhs.pHead = pHead;
   pHead = tempHead;

   list <T> ::Node* tempTail = rhs.pTail;
   rhs.pTail = pTail;
   pTail = tempTail;

   int tempElements = rhs.numElements;
   rhs.numElements = numElements;
   numElements = tempElements;
}

//#endif
}; // namespace custom
