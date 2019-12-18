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
struct thread {int td_flags; int /*<<< orphan*/  td_priority; } ;
struct TYPE_2__ {scalar_t__ ts_estcpu; } ;

/* Variables and functions */
 scalar_t__ ESTCPULIM (scalar_t__) ; 
 int /*<<< orphan*/  KTR_SCHED ; 
 int /*<<< orphan*/  KTR_STATE1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int TDF_NOLOAD ; 
 int /*<<< orphan*/  sched_load_rem () ; 
 int /*<<< orphan*/  sched_tdname (struct thread*) ; 
 TYPE_1__* td_get_sched (struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
sched_exit_thread(struct thread *td, struct thread *child)
{

	KTR_STATE1(KTR_SCHED, "thread", sched_tdname(child), "exit",
	    "prio:%d", child->td_priority);
	thread_lock(td);
	td_get_sched(td)->ts_estcpu = ESTCPULIM(td_get_sched(td)->ts_estcpu +
	    td_get_sched(child)->ts_estcpu);
	thread_unlock(td);
	thread_lock(child);
	if ((child->td_flags & TDF_NOLOAD) == 0)
		sched_load_rem();
	thread_unlock(child);
}