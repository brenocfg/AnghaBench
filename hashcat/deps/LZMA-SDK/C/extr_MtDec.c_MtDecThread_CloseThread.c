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
struct TYPE_3__ {int /*<<< orphan*/  canWrite; int /*<<< orphan*/  canRead; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ CMtDecThread ;

/* Variables and functions */
 int /*<<< orphan*/  Event_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Wait (int /*<<< orphan*/ *) ; 
 scalar_t__ Thread_WasCreated (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MtDecThread_CloseThread(CMtDecThread *t)
{
  if (Thread_WasCreated(&t->thread))
  {
    Event_Set(&t->canWrite); /* we can disable it. There are no threads waiting canWrite in normal cases */
    Event_Set(&t->canRead);
    Thread_Wait(&t->thread);
    Thread_Close(&t->thread);
  }

  Event_Close(&t->canRead);
  Event_Close(&t->canWrite);
}