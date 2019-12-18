#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cs; } ;
struct TYPE_7__ {size_t inBufSize; TYPE_1__ mtProgress; TYPE_2__* threads; scalar_t__ allocatedBufsSize; int /*<<< orphan*/ * mtCallbackObject; int /*<<< orphan*/ * mtCallback; int /*<<< orphan*/ * alloc; int /*<<< orphan*/ * progress; scalar_t__ numFilledThreads; scalar_t__ crossEnd; scalar_t__ crossStart; int /*<<< orphan*/ * crossBlock; int /*<<< orphan*/ * inStream; scalar_t__ numThreadsMax; } ;
struct TYPE_6__ {unsigned int index; int /*<<< orphan*/  thread; int /*<<< orphan*/  canWrite; int /*<<< orphan*/  canRead; int /*<<< orphan*/ * inBuf; TYPE_3__* mtDec; } ;
typedef  TYPE_2__ CMtDecThread ;
typedef  TYPE_3__ CMtDec ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Construct (int /*<<< orphan*/ *) ; 
 unsigned int MTDEC__THREADS_MAX ; 
 int /*<<< orphan*/  Thread_Construct (int /*<<< orphan*/ *) ; 

void MtDec_Construct(CMtDec *p)
{
  unsigned i;
  
  p->inBufSize = (size_t)1 << 18;

  p->numThreadsMax = 0;

  p->inStream = NULL;
  
  // p->inData = NULL;
  // p->inDataSize = 0;

  p->crossBlock = NULL;
  p->crossStart = 0;
  p->crossEnd = 0;

  p->numFilledThreads = 0;

  p->progress = NULL;
  p->alloc = NULL;

  p->mtCallback = NULL;
  p->mtCallbackObject = NULL;

  p->allocatedBufsSize = 0;

  for (i = 0; i < MTDEC__THREADS_MAX; i++)
  {
    CMtDecThread *t = &p->threads[i];
    t->mtDec = p;
    t->index = i;
    t->inBuf = NULL;
    Event_Construct(&t->canRead);
    Event_Construct(&t->canWrite);
    Thread_Construct(&t->thread);
  }

  // Event_Construct(&p->finishedEvent);

  CriticalSection_Init(&p->mtProgress.cs);
}