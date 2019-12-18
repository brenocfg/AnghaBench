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
typedef  scalar_t__ UInt64 ;
struct TYPE_5__ {int /*<<< orphan*/  cs; } ;
struct TYPE_7__ {TYPE_1__ mtProgress; int /*<<< orphan*/  cs; int /*<<< orphan*/  finishedEvent; int /*<<< orphan*/ * writeEvents; TYPE_2__* threads; int /*<<< orphan*/  blocksSemaphore; int /*<<< orphan*/  readEvent; scalar_t__ allocatedBufsSize; int /*<<< orphan*/ * mtCallbackObject; int /*<<< orphan*/ * mtCallback; int /*<<< orphan*/ * allocBig; int /*<<< orphan*/ * progress; scalar_t__ inDataSize; int /*<<< orphan*/ * inData; int /*<<< orphan*/ * inStream; scalar_t__ expectedDataSize; scalar_t__ numThreadsMax; scalar_t__ blockSize; } ;
struct TYPE_6__ {unsigned int index; int /*<<< orphan*/  thread; int /*<<< orphan*/  startEvent; int /*<<< orphan*/  stop; int /*<<< orphan*/ * inBuf; TYPE_3__* mtCoder; } ;
typedef  scalar_t__ Int64 ;
typedef  TYPE_2__ CMtCoderThread ;
typedef  TYPE_3__ CMtCoder ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  False ; 
 unsigned int MTCODER__BLOCKS_MAX ; 
 unsigned int MTCODER__THREADS_MAX ; 
 int /*<<< orphan*/  Semaphore_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Construct (int /*<<< orphan*/ *) ; 

void MtCoder_Construct(CMtCoder *p)
{
  unsigned i;
  
  p->blockSize = 0;
  p->numThreadsMax = 0;
  p->expectedDataSize = (UInt64)(Int64)-1;

  p->inStream = NULL;
  p->inData = NULL;
  p->inDataSize = 0;

  p->progress = NULL;
  p->allocBig = NULL;

  p->mtCallback = NULL;
  p->mtCallbackObject = NULL;

  p->allocatedBufsSize = 0;

  Event_Construct(&p->readEvent);
  Semaphore_Construct(&p->blocksSemaphore);

  for (i = 0; i < MTCODER__THREADS_MAX; i++)
  {
    CMtCoderThread *t = &p->threads[i];
    t->mtCoder = p;
    t->index = i;
    t->inBuf = NULL;
    t->stop = False;
    Event_Construct(&t->startEvent);
    Thread_Construct(&t->thread);
  }

  #ifdef MTCODER__USE_WRITE_THREAD
    for (i = 0; i < MTCODER__BLOCKS_MAX; i++)
      Event_Construct(&p->writeEvents[i]);
  #else
    Event_Construct(&p->finishedEvent);
  #endif

  CriticalSection_Init(&p->cs);
  CriticalSection_Init(&p->mtProgress.cs);
}