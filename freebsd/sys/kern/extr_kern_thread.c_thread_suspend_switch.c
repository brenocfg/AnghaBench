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
struct thread {int /*<<< orphan*/  td_flags; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_suspcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_GIANT () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SLOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int SWT_SUSPEND ; 
 int SW_VOL ; 
 int /*<<< orphan*/  TDF_NEEDSUSPCHK ; 
 int /*<<< orphan*/  TD_IS_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  TD_SET_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  mi_switch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_sleep (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_stopped (struct proc*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
thread_suspend_switch(struct thread *td, struct proc *p)
{

	KASSERT(!TD_IS_SUSPENDED(td), ("already suspended"));
	PROC_LOCK_ASSERT(p, MA_OWNED);
	PROC_SLOCK_ASSERT(p, MA_OWNED);
	/*
	 * We implement thread_suspend_one in stages here to avoid
	 * dropping the proc lock while the thread lock is owned.
	 */
	if (p == td->td_proc) {
		thread_stopped(p);
		p->p_suspcount++;
	}
	PROC_UNLOCK(p);
	thread_lock(td);
	td->td_flags &= ~TDF_NEEDSUSPCHK;
	TD_SET_SUSPENDED(td);
	sched_sleep(td, 0);
	PROC_SUNLOCK(p);
	DROP_GIANT();
	mi_switch(SW_VOL | SWT_SUSPEND, NULL);
	thread_unlock(td);
	PICKUP_GIANT();
	PROC_LOCK(p);
	PROC_SLOCK(p);
}