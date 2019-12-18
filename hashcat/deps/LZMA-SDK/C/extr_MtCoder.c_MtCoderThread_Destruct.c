#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int stop; int /*<<< orphan*/ * inBuf; TYPE_1__* mtCoder; int /*<<< orphan*/  startEvent; int /*<<< orphan*/  thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  allocBig; } ;
typedef  TYPE_2__ CMtCoderThread ;

/* Variables and functions */
 int /*<<< orphan*/  Event_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Wait (int /*<<< orphan*/ *) ; 
 scalar_t__ Thread_WasCreated (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MtCoderThread_Destruct(CMtCoderThread *t)
{
  if (Thread_WasCreated(&t->thread))
  {
    t->stop = 1;
    Event_Set(&t->startEvent);
    Thread_Wait(&t->thread);
    Thread_Close(&t->thread);
  }

  Event_Close(&t->startEvent);

  if (t->inBuf)
  {
    ISzAlloc_Free(t->mtCoder->allocBig, t->inBuf);
    t->inBuf = NULL;
  }
}