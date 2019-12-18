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
struct TYPE_3__ {int /*<<< orphan*/  finishedEvent; int /*<<< orphan*/ * writeEvents; int /*<<< orphan*/  blocksSemaphore; int /*<<< orphan*/  readEvent; int /*<<< orphan*/ * threads; } ;
typedef  TYPE_1__ CMtCoder ;

/* Variables and functions */
 int /*<<< orphan*/  Event_Close (int /*<<< orphan*/ *) ; 
 unsigned int MTCODER__BLOCKS_MAX ; 
 unsigned int MTCODER__THREADS_MAX ; 
 int /*<<< orphan*/  MtCoderThread_Destruct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Semaphore_Close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MtCoder_Free(CMtCoder *p)
{
  unsigned i;

  /*
  p->stopReading = True;
  if (Event_IsCreated(&p->readEvent))
    Event_Set(&p->readEvent);
  */

  for (i = 0; i < MTCODER__THREADS_MAX; i++)
    MtCoderThread_Destruct(&p->threads[i]);

  Event_Close(&p->readEvent);
  Semaphore_Close(&p->blocksSemaphore);

  #ifdef MTCODER__USE_WRITE_THREAD
    for (i = 0; i < MTCODER__BLOCKS_MAX; i++)
      Event_Close(&p->writeEvents[i]);
  #else
    Event_Close(&p->finishedEvent);
  #endif
}