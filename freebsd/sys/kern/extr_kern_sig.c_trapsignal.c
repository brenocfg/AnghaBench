#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_sigmask; struct proc* td_proc; } ;
struct sigacts {scalar_t__* ps_sigact; int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigignore; int /*<<< orphan*/  ps_sigcatch; } ;
struct proc {int p_flag; int p_sig; TYPE_1__* p_sysent; struct sigacts* p_sigacts; } ;
struct TYPE_7__ {int ksi_signo; int ksi_code; } ;
typedef  TYPE_2__ ksiginfo_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* sv_sendsig ) (scalar_t__,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ KTRPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_PSIG ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_TRACED ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 size_t _SIG_IDX (int) ; 
 int /*<<< orphan*/  _SIG_VALID (int) ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ kern_forcesigexit ; 
 int /*<<< orphan*/  ktrpsig (int,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  postsig_done (int,struct thread*,struct sigacts*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdsendsignal (struct proc*,struct thread*,int,TYPE_2__*) ; 

void
trapsignal(struct thread *td, ksiginfo_t *ksi)
{
	struct sigacts *ps;
	struct proc *p;
	int sig;
	int code;

	p = td->td_proc;
	sig = ksi->ksi_signo;
	code = ksi->ksi_code;
	KASSERT(_SIG_VALID(sig), ("invalid signal"));

	PROC_LOCK(p);
	ps = p->p_sigacts;
	mtx_lock(&ps->ps_mtx);
	if ((p->p_flag & P_TRACED) == 0 && SIGISMEMBER(ps->ps_sigcatch, sig) &&
	    !SIGISMEMBER(td->td_sigmask, sig)) {
#ifdef KTRACE
		if (KTRPOINT(curthread, KTR_PSIG))
			ktrpsig(sig, ps->ps_sigact[_SIG_IDX(sig)],
			    &td->td_sigmask, code);
#endif
		(*p->p_sysent->sv_sendsig)(ps->ps_sigact[_SIG_IDX(sig)],
				ksi, &td->td_sigmask);
		postsig_done(sig, td, ps);
		mtx_unlock(&ps->ps_mtx);
	} else {
		/*
		 * Avoid a possible infinite loop if the thread
		 * masking the signal or process is ignoring the
		 * signal.
		 */
		if (kern_forcesigexit &&
		    (SIGISMEMBER(td->td_sigmask, sig) ||
		     ps->ps_sigact[_SIG_IDX(sig)] == SIG_IGN)) {
			SIGDELSET(td->td_sigmask, sig);
			SIGDELSET(ps->ps_sigcatch, sig);
			SIGDELSET(ps->ps_sigignore, sig);
			ps->ps_sigact[_SIG_IDX(sig)] = SIG_DFL;
		}
		mtx_unlock(&ps->ps_mtx);
		p->p_sig = sig;		/* XXX to verify code */
		tdsendsignal(p, td, sig, ksi);
	}
	PROC_UNLOCK(p);
}