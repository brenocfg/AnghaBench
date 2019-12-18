#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread {int /*<<< orphan*/  td_priority; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  KTR_SCHED ; 
 int /*<<< orphan*/  KTR_STATE1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_exit_thread (int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  sched_tdname (struct thread*) ; 

void
sched_exit(struct proc *p, struct thread *td)
{

	KTR_STATE1(KTR_SCHED, "thread", sched_tdname(td), "proc exit",
	    "prio:%d", td->td_priority);

	PROC_LOCK_ASSERT(p, MA_OWNED);
	sched_exit_thread(FIRST_THREAD_IN_PROC(p), td);
}