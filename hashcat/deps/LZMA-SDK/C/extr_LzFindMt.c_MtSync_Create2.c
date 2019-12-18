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
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_3__ {void* wasCreated; int /*<<< orphan*/  thread; void* needStart; int /*<<< orphan*/  filledSemaphore; int /*<<< orphan*/  freeSemaphore; int /*<<< orphan*/  wasStopped; int /*<<< orphan*/  wasStarted; int /*<<< orphan*/  canStart; void* csWasInitialized; int /*<<< orphan*/  cs; } ;
typedef  int /*<<< orphan*/  THREAD_FUNC_TYPE ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CMtSync ;

/* Variables and functions */
 int /*<<< orphan*/  AutoResetEvent_CreateNotSignaled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CriticalSection_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RINOK_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  Semaphore_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Thread_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 void* True ; 

__attribute__((used)) static SRes MtSync_Create2(CMtSync *p, THREAD_FUNC_TYPE startAddress, void *obj, UInt32 numBlocks)
{
  if (p->wasCreated)
    return SZ_OK;

  RINOK_THREAD(CriticalSection_Init(&p->cs));
  p->csWasInitialized = True;

  RINOK_THREAD(AutoResetEvent_CreateNotSignaled(&p->canStart));
  RINOK_THREAD(AutoResetEvent_CreateNotSignaled(&p->wasStarted));
  RINOK_THREAD(AutoResetEvent_CreateNotSignaled(&p->wasStopped));
  
  RINOK_THREAD(Semaphore_Create(&p->freeSemaphore, numBlocks, numBlocks));
  RINOK_THREAD(Semaphore_Create(&p->filledSemaphore, 0, numBlocks));

  p->needStart = True;
  
  RINOK_THREAD(Thread_Create(&p->thread, startAddress, obj));
  p->wasCreated = True;
  return SZ_OK;
}