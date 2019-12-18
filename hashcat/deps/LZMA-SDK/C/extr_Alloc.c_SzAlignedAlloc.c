#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ISzAllocPtr ;

/* Variables and functions */
 size_t ADJUST_ALLOC_SIZE ; 
 int ALLOC_ALIGN_SIZE ; 
 void* MY_ALIGN_PTR_UP_PLUS (void*,int) ; 
 void* MyAlloc (size_t) ; 
 int /*<<< orphan*/  Print (char*) ; 
 int /*<<< orphan*/  PrintAddr (void*) ; 
 int /*<<< orphan*/  PrintHex (size_t,int) ; 
 int /*<<< orphan*/  PrintLn () ; 
 int /*<<< orphan*/  UNUSED_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ posix_memalign (void**,int,size_t) ; 

__attribute__((used)) static void *SzAlignedAlloc(ISzAllocPtr pp, size_t size)
{
  #ifndef USE_posix_memalign
  
  void *p;
  void *pAligned;
  size_t newSize;
  UNUSED_VAR(pp);

  /* also we can allocate additional dummy ALLOC_ALIGN_SIZE bytes after aligned
     block to prevent cache line sharing with another allocated blocks */

  newSize = size + ALLOC_ALIGN_SIZE * 1 + ADJUST_ALLOC_SIZE;
  if (newSize < size)
    return NULL;

  p = MyAlloc(newSize);
  
  if (!p)
    return NULL;
  pAligned = MY_ALIGN_PTR_UP_PLUS(p, ALLOC_ALIGN_SIZE);

  Print(" size="); PrintHex(size, 8);
  Print(" a_size="); PrintHex(newSize, 8);
  Print(" ptr="); PrintAddr(p);
  Print(" a_ptr="); PrintAddr(pAligned);
  PrintLn();

  ((void **)pAligned)[-1] = p;

  return pAligned;

  #else

  void *p;
  UNUSED_VAR(pp);
  if (posix_memalign(&p, ALLOC_ALIGN_SIZE, size))
    return NULL;

  Print(" posix_memalign="); PrintAddr(p);
  PrintLn();

  return p;

  #endif
}