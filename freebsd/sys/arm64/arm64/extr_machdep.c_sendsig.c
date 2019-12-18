#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int* tf_x; void* tf_sp; void* tf_elr; void* tf_lr; } ;
struct TYPE_5__ {int /*<<< orphan*/  ss_flags; scalar_t__ ss_size; scalar_t__ ss_sp; } ;
struct thread {int td_pflags; struct proc* td_proc; TYPE_1__ td_sigstk; struct trapframe* td_frame; } ;
struct sysentvec {scalar_t__ sv_sigcode_base; scalar_t__* sv_szsigcode; scalar_t__ sv_psstrings; } ;
struct TYPE_6__ {TYPE_1__ uc_stack; int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_mcontext; } ;
struct sigframe {TYPE_2__ sf_uc; int /*<<< orphan*/  sf_si; } ;
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigonstack; } ;
struct proc {struct sysentvec* p_sysent; int /*<<< orphan*/  p_comm; struct sigacts* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ sig_t ;
typedef  void* register_t ;
struct TYPE_7__ {int ksi_signo; int /*<<< orphan*/  ksi_info; } ;
typedef  TYPE_3__ ksiginfo_t ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct thread*,struct sigframe*) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct thread*,void*,void*) ; 
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  KTR_SIG ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGILL ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SS_DISABLE ; 
 int /*<<< orphan*/  SS_ONSTACK ; 
 scalar_t__ STACKALIGN (struct sigframe*) ; 
 int TDP_ALTSTACK ; 
 int /*<<< orphan*/  bzero (struct sigframe*,int) ; 
 scalar_t__ copyout (struct sigframe*,struct sigframe*,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  get_fpcontext (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mcontext (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigexit (struct thread*,int /*<<< orphan*/ ) ; 
 int sigonstack (void*) ; 

void
sendsig(sig_t catcher, ksiginfo_t *ksi, sigset_t *mask)
{
	struct thread *td;
	struct proc *p;
	struct trapframe *tf;
	struct sigframe *fp, frame;
	struct sigacts *psp;
	struct sysentvec *sysent;
	int onstack, sig;

	td = curthread;
	p = td->td_proc;
	PROC_LOCK_ASSERT(p, MA_OWNED);

	sig = ksi->ksi_signo;
	psp = p->p_sigacts;
	mtx_assert(&psp->ps_mtx, MA_OWNED);

	tf = td->td_frame;
	onstack = sigonstack(tf->tf_sp);

	CTR4(KTR_SIG, "sendsig: td=%p (%s) catcher=%p sig=%d", td, p->p_comm,
	    catcher, sig);

	/* Allocate and validate space for the signal handler context. */
	if ((td->td_pflags & TDP_ALTSTACK) != 0 && !onstack &&
	    SIGISMEMBER(psp->ps_sigonstack, sig)) {
		fp = (struct sigframe *)((uintptr_t)td->td_sigstk.ss_sp +
		    td->td_sigstk.ss_size);
#if defined(COMPAT_43)
		td->td_sigstk.ss_flags |= SS_ONSTACK;
#endif
	} else {
		fp = (struct sigframe *)td->td_frame->tf_sp;
	}

	/* Make room, keeping the stack aligned */
	fp--;
	fp = (struct sigframe *)STACKALIGN(fp);

	/* Fill in the frame to copy out */
	bzero(&frame, sizeof(frame));
	get_mcontext(td, &frame.sf_uc.uc_mcontext, 0);
	get_fpcontext(td, &frame.sf_uc.uc_mcontext);
	frame.sf_si = ksi->ksi_info;
	frame.sf_uc.uc_sigmask = *mask;
	frame.sf_uc.uc_stack = td->td_sigstk;
	frame.sf_uc.uc_stack.ss_flags = (td->td_pflags & TDP_ALTSTACK) != 0 ?
	    (onstack ? SS_ONSTACK : 0) : SS_DISABLE;
	mtx_unlock(&psp->ps_mtx);
	PROC_UNLOCK(td->td_proc);

	/* Copy the sigframe out to the user's stack. */
	if (copyout(&frame, fp, sizeof(*fp)) != 0) {
		/* Process has trashed its stack. Kill it. */
		CTR2(KTR_SIG, "sendsig: sigexit td=%p fp=%p", td, fp);
		PROC_LOCK(p);
		sigexit(td, SIGILL);
	}

	tf->tf_x[0]= sig;
	tf->tf_x[1] = (register_t)&fp->sf_si;
	tf->tf_x[2] = (register_t)&fp->sf_uc;

	tf->tf_elr = (register_t)catcher;
	tf->tf_sp = (register_t)fp;
	sysent = p->p_sysent;
	if (sysent->sv_sigcode_base != 0)
		tf->tf_lr = (register_t)sysent->sv_sigcode_base;
	else
		tf->tf_lr = (register_t)(sysent->sv_psstrings -
		    *(sysent->sv_szsigcode));

	CTR3(KTR_SIG, "sendsig: return td=%p pc=%#x sp=%#x", td, tf->tf_elr,
	    tf->tf_sp);

	PROC_LOCK(p);
	mtx_lock(&psp->ps_mtx);
}