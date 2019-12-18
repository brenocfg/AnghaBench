#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct trapframe {int* tf_x; int tf_elr; int /*<<< orphan*/  tf_spsr; } ;
struct TYPE_8__ {scalar_t__ ss_size; scalar_t__ ss_sp; int /*<<< orphan*/  ss_flags; } ;
struct thread {int td_pflags; struct proc* td_proc; TYPE_2__ td_sigstk; struct trapframe* td_frame; } ;
struct sysentvec {scalar_t__ sv_sigcode_base; scalar_t__* sv_szsigcode; scalar_t__ sv_psstrings; } ;
struct siginfo32 {int dummy; } ;
struct TYPE_7__ {uintptr_t ss_sp; scalar_t__ ss_size; int /*<<< orphan*/  ss_flags; } ;
struct TYPE_11__ {int mc_vfp_size; void* mc_vfp_ptr; } ;
struct TYPE_9__ {TYPE_1__ uc_stack; int /*<<< orphan*/  uc_sigmask; TYPE_5__ uc_mcontext; } ;
struct sigframe32 {TYPE_3__ sf_uc; struct siginfo32 sf_si; int /*<<< orphan*/  sf_vfp; } ;
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigonstack; } ;
struct proc {struct sysentvec* p_sysent; int /*<<< orphan*/  p_comm; struct sigacts* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ sig_t ;
typedef  int register_t ;
struct TYPE_10__ {int ksi_signo; int ksi_code; int /*<<< orphan*/  ksi_info; } ;
typedef  TYPE_4__ ksiginfo_t ;
typedef  scalar_t__ fp ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct thread*,struct sigframe32*) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct thread*,int,int) ; 
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,struct thread*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  KTR_SIG ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PSR_T ; 
 int /*<<< orphan*/  SIGILL ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SS_DISABLE ; 
 int /*<<< orphan*/  SS_ONSTACK ; 
 int TDP_ALTSTACK ; 
 scalar_t__ copyout (struct sigframe32*,struct sigframe32*,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  get_fpcontext32 (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mcontext32 (struct thread*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigexit (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siginfo_to_siginfo32 (int /*<<< orphan*/ *,struct siginfo32*) ; 
 int sigonstack (int) ; 

void
freebsd32_sendsig(sig_t catcher, ksiginfo_t *ksi, sigset_t *mask)
{
	struct thread *td;
	struct proc *p;
	struct trapframe *tf;
	struct sigframe32 *fp, frame;
	struct sigacts *psp;
	struct siginfo32 siginfo;
	struct sysentvec *sysent;
	int onstack;
	int sig;
	int code;

	siginfo_to_siginfo32(&ksi->ksi_info, &siginfo);
	td = curthread;
	p = td->td_proc;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	sig = ksi->ksi_signo;
	code = ksi->ksi_code;
	psp = p->p_sigacts;
	mtx_assert(&psp->ps_mtx, MA_OWNED);
	tf = td->td_frame;
	onstack = sigonstack(tf->tf_x[13]);

	CTR4(KTR_SIG, "sendsig: td=%p (%s) catcher=%p sig=%d", td, p->p_comm,
	    catcher, sig);

	/* Allocate and validate space for the signal handler context. */
	if ((td->td_pflags & TDP_ALTSTACK) != 0 && !(onstack) &&
	    SIGISMEMBER(psp->ps_sigonstack, sig)) {
		fp = (struct sigframe32 *)((uintptr_t)td->td_sigstk.ss_sp +
		    td->td_sigstk.ss_size);
#if defined(COMPAT_43)
		td->td_sigstk.ss_flags |= SS_ONSTACK;
#endif
	} else
		fp = (struct sigframe32 *)td->td_frame->tf_x[13];

	/* make room on the stack */
	fp--;

	/* make the stack aligned */
	fp = (struct sigframe32 *)((unsigned long)(fp) &~ (8 - 1));
	/* Populate the siginfo frame. */
	get_mcontext32(td, &frame.sf_uc.uc_mcontext, 0);
#ifdef VFP
	get_fpcontext32(td, &frame.sf_vfp);
	frame.sf_uc.uc_mcontext.mc_vfp_size = sizeof(fp->sf_vfp);
	frame.sf_uc.uc_mcontext.mc_vfp_ptr = (uint32_t)(uintptr_t)&fp->sf_vfp;
#else
	frame.sf_uc.uc_mcontext.mc_vfp_size = 0;
	frame.sf_uc.uc_mcontext.mc_vfp_ptr = (uint32_t)NULL;
#endif
	frame.sf_si = siginfo;
	frame.sf_uc.uc_sigmask = *mask;
	frame.sf_uc.uc_stack.ss_flags = (td->td_pflags & TDP_ALTSTACK )
	    ? ((onstack) ? SS_ONSTACK : 0) : SS_DISABLE;
	frame.sf_uc.uc_stack.ss_sp = (uintptr_t)td->td_sigstk.ss_sp;
	frame.sf_uc.uc_stack.ss_size = td->td_sigstk.ss_size;

	mtx_unlock(&psp->ps_mtx);
	PROC_UNLOCK(td->td_proc);

	/* Copy the sigframe out to the user's stack. */
	if (copyout(&frame, fp, sizeof(*fp)) != 0) {
		/* Process has trashed its stack. Kill it. */
		CTR2(KTR_SIG, "sendsig: sigexit td=%p fp=%p", td, fp);
		PROC_LOCK(p);
		sigexit(td, SIGILL);
	}

	/*
	 * Build context to run handler in.  We invoke the handler
	 * directly, only returning via the trampoline.  Note the
	 * trampoline version numbers are coordinated with machine-
	 * dependent code in libc.
	 */

	tf->tf_x[0] = sig;
	tf->tf_x[1] = (register_t)&fp->sf_si;
	tf->tf_x[2] = (register_t)&fp->sf_uc;

	/* the trampoline uses r5 as the uc address */
	tf->tf_x[5] = (register_t)&fp->sf_uc;
	tf->tf_elr = (register_t)catcher;
	tf->tf_x[13] = (register_t)fp;
	sysent = p->p_sysent;
	if (sysent->sv_sigcode_base != 0)
		tf->tf_x[14] = (register_t)sysent->sv_sigcode_base;
	else
		tf->tf_x[14] = (register_t)(sysent->sv_psstrings -
		    *(sysent->sv_szsigcode));
	/* Set the mode to enter in the signal handler */
	if ((register_t)catcher & 1)
		tf->tf_spsr |= PSR_T;
	else
		tf->tf_spsr &= ~PSR_T;

	CTR3(KTR_SIG, "sendsig: return td=%p pc=%#x sp=%#x", td, tf->tf_x[14],
	    tf->tf_x[13]);

	PROC_LOCK(p);
	mtx_lock(&psp->ps_mtx);

}