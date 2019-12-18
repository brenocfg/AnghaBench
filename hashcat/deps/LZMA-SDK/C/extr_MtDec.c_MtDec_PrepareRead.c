#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ crossStart; scalar_t__ crossEnd; unsigned int numStartedThreads; unsigned int numFilledThreads; unsigned int filledThreadStart; int /*<<< orphan*/ * threads; int /*<<< orphan*/ * crossBlock; int /*<<< orphan*/  alloc; } ;
typedef  TYPE_1__ CMtDec ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int MTDEC__THREADS_MAX ; 
 int /*<<< orphan*/  MtDecThread_FreeInBufs (int /*<<< orphan*/ *) ; 

int MtDec_PrepareRead(CMtDec *p)
{
  if (p->crossBlock && p->crossStart == p->crossEnd)
  {
    ISzAlloc_Free(p->alloc, p->crossBlock);
    p->crossBlock = NULL;
  }
    
  {
    unsigned i;
    for (i = 0; i < MTDEC__THREADS_MAX; i++)
      if (i > p->numStartedThreads
          || p->numFilledThreads <=
            (i >= p->filledThreadStart ?
              i - p->filledThreadStart :
              i + p->numStartedThreads - p->filledThreadStart))
        MtDecThread_FreeInBufs(&p->threads[i]);
  }

  return (p->numFilledThreads != 0) || (p->crossStart != p->crossEnd);
}