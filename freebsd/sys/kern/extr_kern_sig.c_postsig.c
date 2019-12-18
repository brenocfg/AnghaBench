#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int td_pflags; int /*<<< orphan*/  td_sigmask; int /*<<< orphan*/  td_oldsigmask; int /*<<< orphan*/  td_sigqueue; struct proc* td_proc; } ;
struct sigacts {scalar_t__* ps_sigact; int /*<<< orphan*/  ps_mtx; } ;
struct proc {int p_stops; int p_sig; TYPE_1__* p_sysent; int /*<<< orphan*/  p_sigqueue; struct sigacts* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ sig_t ;
struct TYPE_8__ {int ksi_signo; scalar_t__ ksi_code; int /*<<< orphan*/  ksi_info; int /*<<< orphan*/  ksi_timerid; } ;
typedef  TYPE_2__ ksiginfo_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* sv_sendsig ) (scalar_t__,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_PSIG ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 scalar_t__ SI_TIMER ; 
 int S_SIG ; 
 int TDP_OLDMASK ; 
 size_t _SIG_IDX (int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  itimer_accept (struct proc*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ktrpsig (int,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  postsig_done (int,struct thread*,struct sigacts*) ; 
 int /*<<< orphan*/  proc_td_siginfo_capture (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigexit (struct thread*,int) ; 
 scalar_t__ sigqueue_get (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  stopevent (struct proc*,int,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_2__*,int /*<<< orphan*/ *) ; 

int
postsig(int sig)
{
	struct thread *td;
	struct proc *p;
	struct sigacts *ps;
	sig_t action;
	ksiginfo_t ksi;
	sigset_t returnmask;

	KASSERT(sig != 0, ("postsig"));

	td = curthread;
	p = td->td_proc;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	ps = p->p_sigacts;
	mtx_assert(&ps->ps_mtx, MA_OWNED);
	ksiginfo_init(&ksi);
	if (sigqueue_get(&td->td_sigqueue, sig, &ksi) == 0 &&
	    sigqueue_get(&p->p_sigqueue, sig, &ksi) == 0)
		return (0);
	ksi.ksi_signo = sig;
	if (ksi.ksi_code == SI_TIMER)
		itimer_accept(p, ksi.ksi_timerid, &ksi);
	action = ps->ps_sigact[_SIG_IDX(sig)];
#ifdef KTRACE
	if (KTRPOINT(td, KTR_PSIG))
		ktrpsig(sig, action, td->td_pflags & TDP_OLDMASK ?
		    &td->td_oldsigmask : &td->td_sigmask, ksi.ksi_code);
#endif
	if ((p->p_stops & S_SIG) != 0) {
		mtx_unlock(&ps->ps_mtx);
		stopevent(p, S_SIG, sig);
		mtx_lock(&ps->ps_mtx);
	}

	if (action == SIG_DFL) {
		/*
		 * Default action, where the default is to kill
		 * the process.  (Other cases were ignored above.)
		 */
		mtx_unlock(&ps->ps_mtx);
		proc_td_siginfo_capture(td, &ksi.ksi_info);
		sigexit(td, sig);
		/* NOTREACHED */
	} else {
		/*
		 * If we get here, the signal must be caught.
		 */
		KASSERT(action != SIG_IGN, ("postsig action %p", action));
		KASSERT(!SIGISMEMBER(td->td_sigmask, sig),
		    ("postsig action: blocked sig %d", sig));

		/*
		 * Set the new mask value and also defer further
		 * occurrences of this signal.
		 *
		 * Special case: user has done a sigsuspend.  Here the
		 * current mask is not of interest, but rather the
		 * mask from before the sigsuspend is what we want
		 * restored after the signal processing is completed.
		 */
		if (td->td_pflags & TDP_OLDMASK) {
			returnmask = td->td_oldsigmask;
			td->td_pflags &= ~TDP_OLDMASK;
		} else
			returnmask = td->td_sigmask;

		if (p->p_sig == sig) {
			p->p_sig = 0;
		}
		(*p->p_sysent->sv_sendsig)(action, &ksi, &returnmask);
		postsig_done(sig, td, ps);
	}
	return (1);
}