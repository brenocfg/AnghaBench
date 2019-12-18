#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
struct trapframe {int sp; int a0; void* ra; void* t9; void* pc; scalar_t__ badvaddr; scalar_t__ a3; void* a1; void* a2; int /*<<< orphan*/  f0; int /*<<< orphan*/  ast; int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; } ;
struct TYPE_11__ {uintptr_t ss_size; scalar_t__ ss_sp; } ;
struct TYPE_9__ {int md_flags; int /*<<< orphan*/  md_tls; } ;
struct thread {int td_pflags; TYPE_3__ td_sigstk; struct trapframe* td_frame; TYPE_1__ td_md; struct proc* td_proc; } ;
struct TYPE_13__ {int si_signo; void* si_addr; void* si_code; } ;
struct TYPE_10__ {int mc_onstack; int mc_fpused; scalar_t__ mc_fpregs; int /*<<< orphan*/ * mc_regs; int /*<<< orphan*/  mc_tls; int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; void* mc_pc; } ;
struct TYPE_12__ {TYPE_2__ uc_mcontext; TYPE_3__ uc_stack; int /*<<< orphan*/  uc_sigmask; } ;
struct sigframe {TYPE_5__ sf_si; TYPE_4__ sf_uc; } ;
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_siginfo; int /*<<< orphan*/  ps_sigonstack; } ;
struct proc {TYPE_6__* p_sysent; struct sigacts* p_sigacts; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ sig_t ;
typedef  void* register_t ;
struct TYPE_15__ {int ksi_signo; void* ksi_code; TYPE_5__ ksi_info; } ;
typedef  TYPE_7__ ksiginfo_t ;
struct TYPE_14__ {void** sv_szsigcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MDTD_FPUSED ; 
 int /*<<< orphan*/  MipsSaveCurFPState (struct thread*) ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ PS_STRINGS ; 
 int /*<<< orphan*/  SIGILL ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int STACK_ALIGN ; 
 int TDP_ALTSTACK ; 
 int /*<<< orphan*/  UCONTEXT_MAGIC ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 int /*<<< orphan*/  bzero (struct sigframe*,int) ; 
 scalar_t__ copyout (struct sigframe*,struct sigframe*,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigexit (struct thread*,int /*<<< orphan*/ ) ; 
 int sigonstack (int) ; 

void
sendsig(sig_t catcher, ksiginfo_t *ksi, sigset_t *mask)
{
	struct proc *p;
	struct thread *td;
	struct trapframe *regs;
	struct sigacts *psp;
	struct sigframe sf, *sfp;
	int sig;
	int oonstack;

	td = curthread;
	p = td->td_proc;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	sig = ksi->ksi_signo;
	psp = p->p_sigacts;
	mtx_assert(&psp->ps_mtx, MA_OWNED);

	regs = td->td_frame;
	oonstack = sigonstack(regs->sp);

	/* save user context */
	bzero(&sf, sizeof(struct sigframe));
	sf.sf_uc.uc_sigmask = *mask;
	sf.sf_uc.uc_stack = td->td_sigstk;
	sf.sf_uc.uc_mcontext.mc_onstack = (oonstack) ? 1 : 0;
	sf.sf_uc.uc_mcontext.mc_pc = regs->pc;
	sf.sf_uc.uc_mcontext.mullo = regs->mullo;
	sf.sf_uc.uc_mcontext.mulhi = regs->mulhi;
	sf.sf_uc.uc_mcontext.mc_tls = td->td_md.md_tls;
	sf.sf_uc.uc_mcontext.mc_regs[0] = UCONTEXT_MAGIC;  /* magic number */
	bcopy((void *)&regs->ast, (void *)&sf.sf_uc.uc_mcontext.mc_regs[1],
	    sizeof(sf.sf_uc.uc_mcontext.mc_regs) - sizeof(register_t));
	sf.sf_uc.uc_mcontext.mc_fpused = td->td_md.md_flags & MDTD_FPUSED;
	if (sf.sf_uc.uc_mcontext.mc_fpused) {
		/* if FPU has current state, save it first */
		if (td == PCPU_GET(fpcurthread))
			MipsSaveCurFPState(td);
		bcopy((void *)&td->td_frame->f0,
		    (void *)sf.sf_uc.uc_mcontext.mc_fpregs,
		    sizeof(sf.sf_uc.uc_mcontext.mc_fpregs));
	}

	/* Allocate and validate space for the signal handler context. */
	if ((td->td_pflags & TDP_ALTSTACK) != 0 && !oonstack &&
	    SIGISMEMBER(psp->ps_sigonstack, sig)) {
		sfp = (struct sigframe *)(((uintptr_t)td->td_sigstk.ss_sp +
		    td->td_sigstk.ss_size - sizeof(struct sigframe))
		    & ~(STACK_ALIGN - 1));
	} else
		sfp = (struct sigframe *)((vm_offset_t)(regs->sp - 
		    sizeof(struct sigframe)) & ~(STACK_ALIGN - 1));

	/* Build the argument list for the signal handler. */
	regs->a0 = sig;
	regs->a2 = (register_t)(intptr_t)&sfp->sf_uc;
	if (SIGISMEMBER(psp->ps_siginfo, sig)) {
		/* Signal handler installed with SA_SIGINFO. */
		regs->a1 = (register_t)(intptr_t)&sfp->sf_si;
		/* sf.sf_ahu.sf_action = (__siginfohandler_t *)catcher; */

		/* fill siginfo structure */
		sf.sf_si = ksi->ksi_info;
		sf.sf_si.si_signo = sig;
		sf.sf_si.si_code = ksi->ksi_code;
		sf.sf_si.si_addr = (void*)(intptr_t)regs->badvaddr;
	} else {
		/* Old FreeBSD-style arguments. */
		regs->a1 = ksi->ksi_code;
		regs->a3 = regs->badvaddr;
		/* sf.sf_ahu.sf_handler = catcher; */
	}

	mtx_unlock(&psp->ps_mtx);
	PROC_UNLOCK(p);

	/*
	 * Copy the sigframe out to the user's stack.
	 */
	if (copyout(&sf, sfp, sizeof(struct sigframe)) != 0) {
		/*
		 * Something is wrong with the stack pointer.
		 * ...Kill the process.
		 */
		PROC_LOCK(p);
		sigexit(td, SIGILL);
	}

	regs->pc = (register_t)(intptr_t)catcher;
	regs->t9 = (register_t)(intptr_t)catcher;
	regs->sp = (register_t)(intptr_t)sfp;
	/*
	 * Signal trampoline code is at base of user stack.
	 */
	regs->ra = (register_t)(intptr_t)PS_STRINGS - *(p->p_sysent->sv_szsigcode);
	PROC_LOCK(p);
	mtx_lock(&psp->ps_mtx);
}