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
typedef  scalar_t__ UInt32 ;
struct TYPE_3__ {scalar_t__ numProcessedBlocks; void* needStart; int /*<<< orphan*/  freeSemaphore; int /*<<< orphan*/  filledSemaphore; int /*<<< orphan*/  wasStopped; scalar_t__ csWasEntered; int /*<<< orphan*/  cs; void* stopWriting; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ CMtSync ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection_Leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Wait (int /*<<< orphan*/ *) ; 
 scalar_t__ False ; 
 int /*<<< orphan*/  Semaphore_Release1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Semaphore_Wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_WasCreated (int /*<<< orphan*/ *) ; 
 void* True ; 

__attribute__((used)) static void MtSync_StopWriting(CMtSync *p)
{
  UInt32 myNumBlocks = p->numProcessedBlocks;
  if (!Thread_WasCreated(&p->thread) || p->needStart)
    return;
  p->stopWriting = True;
  if (p->csWasEntered)
  {
    CriticalSection_Leave(&p->cs);
    p->csWasEntered = False;
  }
  Semaphore_Release1(&p->freeSemaphore);
 
  Event_Wait(&p->wasStopped);

  while (myNumBlocks++ != p->numProcessedBlocks)
  {
    Semaphore_Wait(&p->filledSemaphore);
    Semaphore_Release1(&p->freeSemaphore);
  }
  p->needStart = True;
}