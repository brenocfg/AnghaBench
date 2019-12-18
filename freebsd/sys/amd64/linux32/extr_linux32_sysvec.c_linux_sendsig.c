#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct trapframe {int tf_rflags; int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; void* tf_es; void* tf_ds; void* tf_ss; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_rip; void* tf_rsp; int /*<<< orphan*/  tf_err; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; } ;
struct TYPE_8__ {uintptr_t ss_size; scalar_t__ ss_sp; } ;
struct thread {int td_pflags; int /*<<< orphan*/  td_pcb; TYPE_1__ td_sigstk; struct trapframe* td_frame; struct proc* td_proc; } ;
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigonstack; int /*<<< orphan*/  ps_siginfo; } ;
struct proc {struct sigacts* p_sigacts; } ;
struct TYPE_9__ {int sc_eflags; int /*<<< orphan*/  sc_trapno; scalar_t__ sc_cr2; int /*<<< orphan*/  sc_err; void* sc_ss; void* sc_esp_at_signal; int /*<<< orphan*/  sc_cs; int /*<<< orphan*/  sc_eip; int /*<<< orphan*/  sc_eax; int /*<<< orphan*/  sc_ecx; int /*<<< orphan*/  sc_edx; void* sc_esp; int /*<<< orphan*/  sc_ebx; int /*<<< orphan*/  sc_ebp; int /*<<< orphan*/  sc_esi; int /*<<< orphan*/  sc_edi; void* sc_ds; void* sc_es; int /*<<< orphan*/  sc_fs; int /*<<< orphan*/  sc_gs; int /*<<< orphan*/  sc_mask; } ;
struct l_sigframe {int sf_sig; int /*<<< orphan*/ * sf_extramask; TYPE_2__ sf_sc; void* sf_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  struct l_sigframe* sig_t ;
struct TYPE_10__ {int /*<<< orphan*/  __mask; } ;
typedef  TYPE_3__ l_sigset_t ;
struct TYPE_11__ {int ksi_signo; int ksi_code; scalar_t__ ksi_addr; } ;
typedef  TYPE_4__ ksiginfo_t ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int PSL_D ; 
 int PSL_T ; 
 void* PTROUT (struct l_sigframe*) ; 
 int /*<<< orphan*/  SIGILL ; 
 scalar_t__ SIGISMEMBER (int /*<<< orphan*/ ,int) ; 
 int TDP_ALTSTACK ; 
 int /*<<< orphan*/  TF_HASSEGS ; 
 int /*<<< orphan*/  _ucode32sel ; 
 void* _udatasel ; 
 int /*<<< orphan*/  _ufssel ; 
 int /*<<< orphan*/  _ugssel ; 
 int bsd_to_linux_signal (int) ; 
 int /*<<< orphan*/  bsd_to_linux_sigset (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  bsd_to_linux_trapcode (int) ; 
 int /*<<< orphan*/  bzero (struct l_sigframe*,int) ; 
 scalar_t__ copyout (struct l_sigframe*,struct l_sigframe*,int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  linux32_sigcode ; 
 int /*<<< orphan*/  linux_rt_sendsig (struct l_sigframe*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigexit (struct thread*,int /*<<< orphan*/ ) ; 
 int sigonstack (void*) ; 

__attribute__((used)) static void
linux_sendsig(sig_t catcher, ksiginfo_t *ksi, sigset_t *mask)
{
	struct thread *td = curthread;
	struct proc *p = td->td_proc;
	struct sigacts *psp;
	struct trapframe *regs;
	struct l_sigframe *fp, frame;
	l_sigset_t lmask;
	int oonstack;
	int sig, code;

	sig = ksi->ksi_signo;
	code = ksi->ksi_code;
	PROC_LOCK_ASSERT(p, MA_OWNED);
	psp = p->p_sigacts;
	mtx_assert(&psp->ps_mtx, MA_OWNED);
	if (SIGISMEMBER(psp->ps_siginfo, sig)) {
		/* Signal handler installed with SA_SIGINFO. */
		linux_rt_sendsig(catcher, ksi, mask);
		return;
	}

	regs = td->td_frame;
	oonstack = sigonstack(regs->tf_rsp);

	/* Allocate space for the signal handler context. */
	if ((td->td_pflags & TDP_ALTSTACK) && !oonstack &&
	    SIGISMEMBER(psp->ps_sigonstack, sig)) {
		fp = (struct l_sigframe *)((uintptr_t)td->td_sigstk.ss_sp +
		    td->td_sigstk.ss_size - sizeof(struct l_sigframe));
	} else
		fp = (struct l_sigframe *)regs->tf_rsp - 1;
	mtx_unlock(&psp->ps_mtx);
	PROC_UNLOCK(p);

	/* Build the argument list for the signal handler. */
	sig = bsd_to_linux_signal(sig);

	bzero(&frame, sizeof(frame));

	frame.sf_handler = PTROUT(catcher);
	frame.sf_sig = sig;

	bsd_to_linux_sigset(mask, &lmask);

	/* Build the signal context to be used by sigreturn. */
	frame.sf_sc.sc_mask   = lmask.__mask;
	frame.sf_sc.sc_gs     = regs->tf_gs;
	frame.sf_sc.sc_fs     = regs->tf_fs;
	frame.sf_sc.sc_es     = regs->tf_es;
	frame.sf_sc.sc_ds     = regs->tf_ds;
	frame.sf_sc.sc_edi    = regs->tf_rdi;
	frame.sf_sc.sc_esi    = regs->tf_rsi;
	frame.sf_sc.sc_ebp    = regs->tf_rbp;
	frame.sf_sc.sc_ebx    = regs->tf_rbx;
	frame.sf_sc.sc_esp    = regs->tf_rsp;
	frame.sf_sc.sc_edx    = regs->tf_rdx;
	frame.sf_sc.sc_ecx    = regs->tf_rcx;
	frame.sf_sc.sc_eax    = regs->tf_rax;
	frame.sf_sc.sc_eip    = regs->tf_rip;
	frame.sf_sc.sc_cs     = regs->tf_cs;
	frame.sf_sc.sc_eflags = regs->tf_rflags;
	frame.sf_sc.sc_esp_at_signal = regs->tf_rsp;
	frame.sf_sc.sc_ss     = regs->tf_ss;
	frame.sf_sc.sc_err    = regs->tf_err;
	frame.sf_sc.sc_cr2    = (u_int32_t)(uintptr_t)ksi->ksi_addr;
	frame.sf_sc.sc_trapno = bsd_to_linux_trapcode(code);

	frame.sf_extramask[0] = lmask.__mask;

	if (copyout(&frame, fp, sizeof(frame)) != 0) {
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
		PROC_LOCK(p);
		sigexit(td, SIGILL);
	}

	/* Build context to run handler in. */
	regs->tf_rsp = PTROUT(fp);
	regs->tf_rip = linux32_sigcode;
	regs->tf_rflags &= ~(PSL_T | PSL_D);
	regs->tf_cs = _ucode32sel;
	regs->tf_ss = _udatasel;
	regs->tf_ds = _udatasel;
	regs->tf_es = _udatasel;
	regs->tf_fs = _ufssel;
	regs->tf_gs = _ugssel;
	regs->tf_flags = TF_HASSEGS;
	set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
	PROC_LOCK(p);
	mtx_lock(&psp->ps_mtx);
}