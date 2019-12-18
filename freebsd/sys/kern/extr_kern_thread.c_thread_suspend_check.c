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
struct thread {int td_flags; struct proc* td_proc; } ;
struct proc {int p_flag; scalar_t__ p_numthreads; scalar_t__ p_suspcount; int /*<<< orphan*/  p_boundary_count; struct thread* p_singlethread; TYPE_1__* p_sysent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sv_thread_detach ) (struct thread*) ;} ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ P_SHOULDSTOP (struct proc*) ; 
 int P_SINGLE_BOUNDARY ; 
 int P_SINGLE_EXIT ; 
 scalar_t__ P_STOPPED_SINGLE ; 
 int SWT_SUSPEND ; 
 int SW_INVOL ; 
 int TDF_BOUNDARY ; 
 int TDF_SBDRY ; 
 int TDF_SEINTR ; 
 int TDF_SERESTART ; 
 int TD_SBDRY_ERRNO (struct thread*) ; 
 scalar_t__ TD_SBDRY_INTR (struct thread*) ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  kern_thr_exit (struct thread*) ; 
 int /*<<< orphan*/  kick_proc0 () ; 
 int /*<<< orphan*/  mi_switch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_stopped (struct proc*) ; 
 scalar_t__ thread_suspend_check_needed () ; 
 int /*<<< orphan*/  thread_suspend_one (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int thread_unsuspend_one (struct thread*,struct proc*,int) ; 
 int /*<<< orphan*/  umtx_thread_exit (struct thread*) ; 

int
thread_suspend_check(int return_instead)
{
	struct thread *td;
	struct proc *p;
	int wakeup_swapper;

	td = curthread;
	p = td->td_proc;
	mtx_assert(&Giant, MA_NOTOWNED);
	PROC_LOCK_ASSERT(p, MA_OWNED);
	while (thread_suspend_check_needed()) {
		if (P_SHOULDSTOP(p) == P_STOPPED_SINGLE) {
			KASSERT(p->p_singlethread != NULL,
			    ("singlethread not set"));
			/*
			 * The only suspension in action is a
			 * single-threading. Single threader need not stop.
			 * It is safe to access p->p_singlethread unlocked
			 * because it can only be set to our address by us.
			 */
			if (p->p_singlethread == td)
				return (0);	/* Exempt from stopping. */
		}
		if ((p->p_flag & P_SINGLE_EXIT) && return_instead)
			return (EINTR);

		/* Should we goto user boundary if we didn't come from there? */
		if (P_SHOULDSTOP(p) == P_STOPPED_SINGLE &&
		    (p->p_flag & P_SINGLE_BOUNDARY) && return_instead)
			return (ERESTART);

		/*
		 * Ignore suspend requests if they are deferred.
		 */
		if ((td->td_flags & TDF_SBDRY) != 0) {
			KASSERT(return_instead,
			    ("TDF_SBDRY set for unsafe thread_suspend_check"));
			KASSERT((td->td_flags & (TDF_SEINTR | TDF_SERESTART)) !=
			    (TDF_SEINTR | TDF_SERESTART),
			    ("both TDF_SEINTR and TDF_SERESTART"));
			return (TD_SBDRY_INTR(td) ? TD_SBDRY_ERRNO(td) : 0);
		}

		/*
		 * If the process is waiting for us to exit,
		 * this thread should just suicide.
		 * Assumes that P_SINGLE_EXIT implies P_STOPPED_SINGLE.
		 */
		if ((p->p_flag & P_SINGLE_EXIT) && (p->p_singlethread != td)) {
			PROC_UNLOCK(p);

			/*
			 * Allow Linux emulation layer to do some work
			 * before thread suicide.
			 */
			if (__predict_false(p->p_sysent->sv_thread_detach != NULL))
				(p->p_sysent->sv_thread_detach)(td);
			umtx_thread_exit(td);
			kern_thr_exit(td);
			panic("stopped thread did not exit");
		}

		PROC_SLOCK(p);
		thread_stopped(p);
		if (P_SHOULDSTOP(p) == P_STOPPED_SINGLE) {
			if (p->p_numthreads == p->p_suspcount + 1) {
				thread_lock(p->p_singlethread);
				wakeup_swapper = thread_unsuspend_one(
				    p->p_singlethread, p, false);
				thread_unlock(p->p_singlethread);
				if (wakeup_swapper)
					kick_proc0();
			}
		}
		PROC_UNLOCK(p);
		thread_lock(td);
		/*
		 * When a thread suspends, it just
		 * gets taken off all queues.
		 */
		thread_suspend_one(td);
		if (return_instead == 0) {
			p->p_boundary_count++;
			td->td_flags |= TDF_BOUNDARY;
		}
		PROC_SUNLOCK(p);
		mi_switch(SW_INVOL | SWT_SUSPEND, NULL);
		thread_unlock(td);
		PROC_LOCK(p);
	}
	return (0);
}