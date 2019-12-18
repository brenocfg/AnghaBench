#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UInt64 ;
struct TYPE_8__ {scalar_t__ numFilledThreads; size_t filledThreadStart; size_t numStartedThreads; size_t inBufSize; size_t crossEnd; size_t crossStart; void* crossBlock; int /*<<< orphan*/  alloc; TYPE_1__* threads; } ;
struct TYPE_7__ {void* next; } ;
struct TYPE_6__ {void* inBuf; scalar_t__ inDataSize; size_t inDataSize_Start; } ;
typedef  TYPE_1__ CMtDecThread ;
typedef  TYPE_2__ CMtDecBufLink ;
typedef  TYPE_3__ CMtDec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * MTDEC__DATA_PTR_FROM_LINK (void*) ; 
 int /*<<< orphan*/  MtDecThread_FreeInBufs (TYPE_1__*) ; 

const Byte *MtDec_Read(CMtDec *p, size_t *inLim)
{
  while (p->numFilledThreads != 0)
  {
    CMtDecThread *t = &p->threads[p->filledThreadStart];
    
    if (*inLim != 0)
    {
      {
        void *link = t->inBuf;
        void *next = ((CMtDecBufLink *)link)->next;
        ISzAlloc_Free(p->alloc, link);
        t->inBuf = next;
      }
      
      if (t->inDataSize == 0)
      {
        MtDecThread_FreeInBufs(t);
        if (--p->numFilledThreads == 0)
          break;
        if (++p->filledThreadStart == p->numStartedThreads)
          p->filledThreadStart = 0;
        t = &p->threads[p->filledThreadStart];
      }
    }
    
    {
      size_t lim = t->inDataSize_Start;
      if (lim != 0)
        t->inDataSize_Start = 0;
      else
      {
        UInt64 rem = t->inDataSize;
        lim = p->inBufSize;
        if (lim > rem)
          lim = (size_t)rem;
      }
      t->inDataSize -= lim;
      *inLim = lim;
      return (const Byte *)MTDEC__DATA_PTR_FROM_LINK(t->inBuf);
    }
  }

  {
    size_t crossSize = p->crossEnd - p->crossStart;
    if (crossSize != 0)
    {
      const Byte *data = MTDEC__DATA_PTR_FROM_LINK(p->crossBlock) + p->crossStart;
      *inLim = crossSize;
      p->crossStart = 0;
      p->crossEnd = 0;
      return data;
    }
    *inLim = 0;
    if (p->crossBlock)
    {
      ISzAlloc_Free(p->alloc, p->crossBlock);
      p->crossBlock = NULL;
    }
    return NULL;
  }
}