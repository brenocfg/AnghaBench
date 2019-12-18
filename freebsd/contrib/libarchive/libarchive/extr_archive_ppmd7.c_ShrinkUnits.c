#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* FreeList; } ;
typedef  TYPE_1__ CPpmd7 ;

/* Variables and functions */
 int /*<<< orphan*/  InsertNode (TYPE_1__*,void*,unsigned int) ; 
 int /*<<< orphan*/  MyMem12Cpy (void*,void*,unsigned int) ; 
 void* RemoveNode (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  SplitBlock (TYPE_1__*,void*,unsigned int,unsigned int) ; 
 unsigned int U2I (unsigned int) ; 

__attribute__((used)) static void *ShrinkUnits(CPpmd7 *p, void *oldPtr, unsigned oldNU, unsigned newNU)
{
  unsigned i0 = U2I(oldNU);
  unsigned i1 = U2I(newNU);
  if (i0 == i1)
    return oldPtr;
  if (p->FreeList[i1] != 0)
  {
    void *ptr = RemoveNode(p, i1);
    MyMem12Cpy(ptr, oldPtr, newNU);
    InsertNode(p, oldPtr, i0);
    return ptr;
  }
  SplitBlock(p, oldPtr, i0, i1);
  return oldPtr;
}