#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_priority; } ;
struct TYPE_2__ {scalar_t__ ts_runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCHED ; 
 int /*<<< orphan*/  KTR_STATE1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_interact_update (struct thread*) ; 
 int /*<<< orphan*/  sched_priority (struct thread*) ; 
 int /*<<< orphan*/  sched_tdname (struct thread*) ; 
 TYPE_1__* td_get_sched (struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
sched_exit_thread(struct thread *td, struct thread *child)
{

	KTR_STATE1(KTR_SCHED, "thread", sched_tdname(child), "thread exit",
	    "prio:%d", child->td_priority);
	/*
	 * Give the child's runtime to the parent without returning the
	 * sleep time as a penalty to the parent.  This causes shells that
	 * launch expensive things to mark their children as expensive.
	 */
	thread_lock(td);
	td_get_sched(td)->ts_runtime += td_get_sched(child)->ts_runtime;
	sched_interact_update(td);
	sched_priority(td);
	thread_unlock(td);
}