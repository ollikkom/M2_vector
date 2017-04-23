#ifndef M2_VECTOR_TVECTOR_H
#define M2_VECTOR_TVECTOR_H
#include <string>
#include <iostream>

template <typename T>
class TVector
{
public:
    using value_type = T;
    using size_type = size_t;
    using iterator = value_type *;
    using reference = value_type&;
    using const_reference = const value_type&;

private:
    value_type * Ptr;
    size_type Count;
    size_type InternalCapacity;
public:
    TVector()
            : Ptr(nullptr)
            , Count(0)
            , InternalCapacity(0)
    { }

    TVector(size_type capacity)
            : Count(0)
            , InternalCapacity(capacity)
    {
        Ptr = new value_type[InternalCapacity];
    }

    ~TVector()
    {
        delete[] Ptr;
    }

    bool empty() const throw()
    {
        return size() == 0;
    }

    size_type size() const throw()
    {
        return Count;
    }

    size_type capacity() const throw()
    {
        return InternalCapacity;
    }

    iterator begin() const throw()
    {
        return Ptr;
    }

    iterator end() const throw()
    {
        return Ptr + Count;
    }

    void reserve(size_type size)
    {
        if (InternalCapacity > size) return;
        value_type *pP = new value_type[size];
        memcpy(pP, Ptr, Count * sizeof(value_type));
        delete[] Ptr;
        Ptr = pP;
        InternalCapacity = size;
    }

    TVector(const TVector& rhs)
    {
        InternalCapacity = rhs.InternalCapacity;
        Count = rhs.Count;
        std::copy(rhs.begin(), rhs.end(), this->begin());
    }

    TVector& operator=(const TVector& rhs)
    {
        if (this == &rhs) return *this;
        InternalCapacity = rhs.InternalCapacity;
        Count = rhs.Count;
        delete[] Ptr;
        std::copy(rhs.begin(), rhs.end(), this->begin());
        return *this;
    }

    void push_back(const value_type& value)
    {
        if (InternalCapacity == 0)
            this->reserve(1);
        if (Count < InternalCapacity)
        {
            Ptr[Count] = value;
            Count++;
        }
        else
        {
            this->reserve(InternalCapacity *2);
            Ptr[Count] = value;
            Count++;
        }

    }

    reference at(size_type index)
    {
        if (index >= 0 && index < Count)
            return Ptr[index];
        else
            throw std::out_of_range("Check the index!\n");
    }

    value_type at(size_type index) const
    {
        if (index >= 0 && index < Count)
            return Ptr[index];
        else
            throw std::out_of_range("Check the index!\n");
    }

    reference operator[](size_type index)
    {
        return Ptr[index];
    }

    const_reference operator[](size_type index) const
    {
        return Ptr[index];
    }

    reference front()
    {
        Emptiness();
        return Ptr[0];
    }

    void Emptiness() const
    {
        if (Ptr == nullptr)
            throw std::out_of_range("Check the index!");
    }

    const_reference front() const
    {
        Emptiness();
        return Ptr[0];
    }

    reference back()
    {
        Emptiness();
        return Ptr[Count-1];
    }

    const_reference back() const
    {
        Emptiness();
        return Ptr[Count-1];
    }

    void clear()
    {
        delete[] Ptr;
        Count = 0;
        InternalCapacity = 0;
    }

    void pop_back()
    {
        if(Count != 0)
            Count--;

    }

    void swap(TVector& other) throw()
    {
        std::swap(Ptr, other.Ptr);
        std::swap(InternalCapacity, other.InternalCapacity);
        std::swap(Count, other.Count);

    }

    void resize(size_type count, value_type value = value_type())
    {
        if (Count == count)
            return;
        value_type *pP = new value_type[count];

        if (count < Count)
        {
            memcpy(pP, Ptr, count * sizeof(value_type));
        }
        else
        {
            memcpy(pP, Ptr, Count * sizeof(value_type));
            InternalCapacity = count;
            for ( size_type i = Count; i < count; i++)
            {
                pP[i] = value;
            }
        }
        Count = count;
        delete[] Ptr;
        Ptr = pP;
    }

    iterator insert(iterator pos, const value_type& value)
    {
        if (Ptr + Count < pos)
            throw std::out_of_range("Check the index!\n");

        size_type posP = pos - Ptr;
        if (Count >= InternalCapacity)
            this->reserve(InternalCapacity *2);
        for (size_type i = Count - 1; i >= posP; i--)
        {
            Ptr[i + 1] = Ptr[i];
        }
        Ptr[posP] = value;
        Count++;
        return pos;


    }

    void insert(iterator pos, size_type count, const value_type& value)
    {
        if (Ptr + Count < pos)
            throw std::out_of_range("Incorrect index!\n");

        while (InternalCapacity < Count + count)
            this->reserve(InternalCapacity *2);
        size_type posT = pos - Ptr;
        for (size_type i = Count - 1; i >= posT; i--)
        {
            Ptr[i + count] = Ptr[i];
        }
        for (size_type i = posT; i < posT + count; i++)
        {
            Ptr[i] = value;
        }
        Count += count;
    }

    iterator erase(iterator pos)
    {
        if ( pos > Ptr + Count)
            throw std::out_of_range("Check the index!\n");
        size_type posT = pos - Ptr;
        for (size_type i = posT; i < Count - 1; i++)
        {
            Ptr[i] = Ptr[i + 1];
        }
        Count--;
        return pos;
    }

    iterator erase(iterator first, iterator last)
    {
        if (first > Ptr + Count || last >Ptr + Count)
            throw std::out_of_range("Check the index!\n");
        size_type posF = first - Ptr;
        size_type posL = last - Ptr;
        size_type k=posL-posF;
        for (size_type i = posF; i < Count - k; i++)
        {
            Ptr[i] = Ptr[i + k];
        }
        Count -= posL;
        return first;
    }
};


#endif //M2_VECTOR_TVECTOR_H
