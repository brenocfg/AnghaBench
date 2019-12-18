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
struct thread {int td_pflags; int td_dbgflags; struct proc* td_rfppwait_p; struct proc* td_proc; } ;
struct proc {int p_flag; int p_ptevents; int /*<<< orphan*/  p_mtx; int /*<<< orphan*/  p_pwait; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int PTRACE_VFORK ; 
 int P_PPWAIT ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int TDB_VFORK ; 
 int TDP_RFPPWAIT ; 
 int /*<<< orphan*/  cv_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ptracestop (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_suspend_check (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_suspend_check_needed () ; 

void
fork_rfppwait(struct thread *td)
{
	struct proc *p, *p2;

	MPASS(td->td_pflags & TDP_RFPPWAIT);

	p = td->td_proc;
	/*
	 * Preserve synchronization semantics of vfork.  If
	 * waiting for child to exec or exit, fork set
	 * P_PPWAIT on child, and there we sleep on our proc
	 * (in case of exit).
	 *
	 * Do it after the ptracestop() above is finished, to
	 * not block our debugger until child execs or exits
	 * to finish vfork wait.
	 */
	td->td_pflags &= ~TDP_RFPPWAIT;
	p2 = td->td_rfppwait_p;
again:
	PROC_LOCK(p2);
	while (p2->p_flag & P_PPWAIT) {
		PROC_LOCK(p);
		if (thread_suspend_check_needed()) {
			PROC_UNLOCK(p2);
			thread_suspend_check(0);
			PROC_UNLOCK(p);
			goto again;
		} else {
			PROC_UNLOCK(p);
		}
		cv_timedwait(&p2->p_pwait, &p2->p_mtx, hz);
	}
	PROC_UNLOCK(p2);

	if (td->td_dbgflags & TDB_VFORK) {
		PROC_LOCK(p);
		if (p->p_ptevents & PTRACE_VFORK)
			ptracestop(td, SIGTRAP, NULL);
		td->td_dbgflags &= ~TDB_VFORK;
		PROC_UNLOCK(p);
	}
}