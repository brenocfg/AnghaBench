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
struct thread {int td_pflags; int td_flags; int td_dbgflags; int /*<<< orphan*/ * td_lock; int /*<<< orphan*/  td_name; } ;
struct sleepqueue_chain {int /*<<< orphan*/  sc_lock; } ;
struct sleepqueue {int dummy; } ;
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigintr; } ;
struct proc {struct sigacts* p_sigacts; scalar_t__ p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,void*,long,int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PROC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct sleepqueue_chain* SC_LOOKUP (void*) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int TDB_FSTP ; 
 int TDF_NEEDSIGCHK ; 
 int TDF_NEEDSUSPCHK ; 
 int TDF_SBDRY ; 
 int TDF_SEINTR ; 
 int TDF_SERESTART ; 
 int TDP_WAKEUP ; 
 scalar_t__ TD_ON_SLEEPQ (struct thread*) ; 
 int TD_SBDRY_ERRNO (struct thread*) ; 
 int TD_SBDRY_INTR (struct thread*) ; 
 struct proc* curproc ; 
 int cursig (struct thread*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct sleepqueue* sleepq_lookup (void*) ; 
 scalar_t__ sleepq_resume_thread (struct sleepqueue*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_switch (void*,int) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int thread_suspend_check (int) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static int
sleepq_catch_signals(void *wchan, int pri)
{
	struct sleepqueue_chain *sc;
	struct sleepqueue *sq;
	struct thread *td;
	struct proc *p;
	struct sigacts *ps;
	int sig, ret;

	ret = 0;
	td = curthread;
	p = curproc;
	sc = SC_LOOKUP(wchan);
	mtx_assert(&sc->sc_lock, MA_OWNED);
	MPASS(wchan != NULL);
	if ((td->td_pflags & TDP_WAKEUP) != 0) {
		td->td_pflags &= ~TDP_WAKEUP;
		ret = EINTR;
		thread_lock(td);
		goto out;
	}

	/*
	 * See if there are any pending signals or suspension requests for this
	 * thread.  If not, we can switch immediately.
	 */
	thread_lock(td);
	if ((td->td_flags & (TDF_NEEDSIGCHK | TDF_NEEDSUSPCHK)) != 0) {
		thread_unlock(td);
		mtx_unlock_spin(&sc->sc_lock);
		CTR3(KTR_PROC, "sleepq catching signals: thread %p (pid %ld, %s)",
			(void *)td, (long)p->p_pid, td->td_name);
		PROC_LOCK(p);
		/*
		 * Check for suspension first. Checking for signals and then
		 * suspending could result in a missed signal, since a signal
		 * can be delivered while this thread is suspended.
		 */
		if ((td->td_flags & TDF_NEEDSUSPCHK) != 0) {
			ret = thread_suspend_check(1);
			MPASS(ret == 0 || ret == EINTR || ret == ERESTART);
			if (ret != 0) {
				PROC_UNLOCK(p);
				mtx_lock_spin(&sc->sc_lock);
				thread_lock(td);
				goto out;
			}
		}
		if ((td->td_flags & TDF_NEEDSIGCHK) != 0) {
			ps = p->p_sigacts;
			mtx_lock(&ps->ps_mtx);
			sig = cursig(td);
			if (sig == -1) {
				mtx_unlock(&ps->ps_mtx);
				KASSERT((td->td_flags & TDF_SBDRY) != 0,
				    ("lost TDF_SBDRY"));
				KASSERT(TD_SBDRY_INTR(td),
				    ("lost TDF_SERESTART of TDF_SEINTR"));
				KASSERT((td->td_flags &
				    (TDF_SEINTR | TDF_SERESTART)) !=
				    (TDF_SEINTR | TDF_SERESTART),
				    ("both TDF_SEINTR and TDF_SERESTART"));
				ret = TD_SBDRY_ERRNO(td);
			} else if (sig != 0) {
				ret = SIGISMEMBER(ps->ps_sigintr, sig) ?
				    EINTR : ERESTART;
				mtx_unlock(&ps->ps_mtx);
			} else {
				mtx_unlock(&ps->ps_mtx);
			}

			/*
			 * Do not go into sleep if this thread was the
			 * ptrace(2) attach leader.  cursig() consumed
			 * SIGSTOP from PT_ATTACH, but we usually act
			 * on the signal by interrupting sleep, and
			 * should do that here as well.
			 */
			if ((td->td_dbgflags & TDB_FSTP) != 0) {
				if (ret == 0)
					ret = EINTR;
				td->td_dbgflags &= ~TDB_FSTP;
			}
		}
		/*
		 * Lock the per-process spinlock prior to dropping the PROC_LOCK
		 * to avoid a signal delivery race.  PROC_LOCK, PROC_SLOCK, and
		 * thread_lock() are currently held in tdsendsignal().
		 */
		PROC_SLOCK(p);
		mtx_lock_spin(&sc->sc_lock);
		PROC_UNLOCK(p);
		thread_lock(td);
		PROC_SUNLOCK(p);
	}
	if (ret == 0) {
		sleepq_switch(wchan, pri);
		return (0);
	}
out:
	/*
	 * There were pending signals and this thread is still
	 * on the sleep queue, remove it from the sleep queue.
	 */
	if (TD_ON_SLEEPQ(td)) {
		sq = sleepq_lookup(wchan);
		if (sleepq_resume_thread(sq, td, 0)) {
#ifdef INVARIANTS
			/*
			 * This thread hasn't gone to sleep yet, so it
			 * should not be swapped out.
			 */
			panic("not waking up swapper");
#endif
		}
	}
	mtx_unlock_spin(&sc->sc_lock);
	MPASS(td->td_lock != &sc->sc_lock);
	return (ret);
}