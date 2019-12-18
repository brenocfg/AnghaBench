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
struct thread {scalar_t__ td_priority; int td_flags; int /*<<< orphan*/  td_sigqueue; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_sigqueue; } ;
typedef  scalar_t__ sig_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SUNLOCK (struct proc*) ; 
 scalar_t__ PUSER ; 
 int SIGPROP_CONT ; 
 int SIGPROP_KILL ; 
 int SIGPROP_STOP ; 
 scalar_t__ SIG_DFL ; 
 int TDF_SBDRY ; 
 int TDF_SEINTR ; 
 int TDF_SERESTART ; 
 int TDF_SINTR ; 
 int /*<<< orphan*/  TD_IS_IDLETHREAD (struct thread*) ; 
 scalar_t__ TD_IS_RUNNING (struct thread*) ; 
 scalar_t__ TD_ON_SLEEPQ (struct thread*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  forward_signal (struct thread*) ; 
 int /*<<< orphan*/  kick_proc0 () ; 
 int /*<<< orphan*/  sched_prio (struct thread*,scalar_t__) ; 
 int sigprop (int) ; 
 int /*<<< orphan*/  sigqueue_delete (int /*<<< orphan*/ *,int) ; 
 int sleepq_abort (struct thread*,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static void
tdsigwakeup(struct thread *td, int sig, sig_t action, int intrval)
{
	struct proc *p = td->td_proc;
	int prop;
	int wakeup_swapper;

	wakeup_swapper = 0;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	prop = sigprop(sig);

	PROC_SLOCK(p);
	thread_lock(td);
	/*
	 * Bring the priority of a thread up if we want it to get
	 * killed in this lifetime.  Be careful to avoid bumping the
	 * priority of the idle thread, since we still allow to signal
	 * kernel processes.
	 */
	if (action == SIG_DFL && (prop & SIGPROP_KILL) != 0 &&
	    td->td_priority > PUSER && !TD_IS_IDLETHREAD(td))
		sched_prio(td, PUSER);
	if (TD_ON_SLEEPQ(td)) {
		/*
		 * If thread is sleeping uninterruptibly
		 * we can't interrupt the sleep... the signal will
		 * be noticed when the process returns through
		 * trap() or syscall().
		 */
		if ((td->td_flags & TDF_SINTR) == 0)
			goto out;
		/*
		 * If SIGCONT is default (or ignored) and process is
		 * asleep, we are finished; the process should not
		 * be awakened.
		 */
		if ((prop & SIGPROP_CONT) && action == SIG_DFL) {
			thread_unlock(td);
			PROC_SUNLOCK(p);
			sigqueue_delete(&p->p_sigqueue, sig);
			/*
			 * It may be on either list in this state.
			 * Remove from both for now.
			 */
			sigqueue_delete(&td->td_sigqueue, sig);
			return;
		}

		/*
		 * Don't awaken a sleeping thread for SIGSTOP if the
		 * STOP signal is deferred.
		 */
		if ((prop & SIGPROP_STOP) != 0 && (td->td_flags & (TDF_SBDRY |
		    TDF_SERESTART | TDF_SEINTR)) == TDF_SBDRY)
			goto out;

		/*
		 * Give low priority threads a better chance to run.
		 */
		if (td->td_priority > PUSER && !TD_IS_IDLETHREAD(td))
			sched_prio(td, PUSER);

		wakeup_swapper = sleepq_abort(td, intrval);
	} else {
		/*
		 * Other states do nothing with the signal immediately,
		 * other than kicking ourselves if we are running.
		 * It will either never be noticed, or noticed very soon.
		 */
#ifdef SMP
		if (TD_IS_RUNNING(td) && td != curthread)
			forward_signal(td);
#endif
	}
out:
	PROC_SUNLOCK(p);
	thread_unlock(td);
	if (wakeup_swapper)
		kick_proc0();
}