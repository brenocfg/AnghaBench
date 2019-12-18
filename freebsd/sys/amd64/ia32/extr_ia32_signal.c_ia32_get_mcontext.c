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
struct trapframe {int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rflags; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_fs; int /*<<< orphan*/  tf_gs; } ;
struct thread {struct trapframe* td_frame; struct pcb* td_pcb; } ;
struct pcb {int /*<<< orphan*/  pcb_gsbase; int /*<<< orphan*/  pcb_fsbase; } ;
struct ia32_mcontext {int mc_len; int /*<<< orphan*/  mc_spare2; scalar_t__ mc_xfpustate_len; scalar_t__ mc_xfpustate; int /*<<< orphan*/  mc_gsbase; int /*<<< orphan*/  mc_fsbase; int /*<<< orphan*/  mc_flags; int /*<<< orphan*/  mc_ss; int /*<<< orphan*/  mc_esp; int /*<<< orphan*/  mc_cs; int /*<<< orphan*/  mc_eip; int /*<<< orphan*/  mc_ecx; int /*<<< orphan*/  mc_ebx; int /*<<< orphan*/  mc_edx; int /*<<< orphan*/  mc_eax; int /*<<< orphan*/  mc_eflags; int /*<<< orphan*/  mc_isp; int /*<<< orphan*/  mc_ebp; int /*<<< orphan*/  mc_esi; int /*<<< orphan*/  mc_edi; int /*<<< orphan*/  mc_ds; int /*<<< orphan*/  mc_es; int /*<<< orphan*/  mc_fs; int /*<<< orphan*/  mc_gs; int /*<<< orphan*/  mc_onstack; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int GET_MC_CLEAR_RET ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSL_C ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  ia32_get_fpcontext (struct thread*,struct ia32_mcontext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigonstack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ia32_get_mcontext(struct thread *td, struct ia32_mcontext *mcp, int flags)
{
	struct pcb *pcb;
	struct trapframe *tp;

	pcb = td->td_pcb;
	tp = td->td_frame;

	PROC_LOCK(curthread->td_proc);
	mcp->mc_onstack = sigonstack(tp->tf_rsp);
	PROC_UNLOCK(curthread->td_proc);
	/* Entry into kernel always sets TF_HASSEGS */
	mcp->mc_gs = tp->tf_gs;
	mcp->mc_fs = tp->tf_fs;
	mcp->mc_es = tp->tf_es;
	mcp->mc_ds = tp->tf_ds;
	mcp->mc_edi = tp->tf_rdi;
	mcp->mc_esi = tp->tf_rsi;
	mcp->mc_ebp = tp->tf_rbp;
	mcp->mc_isp = tp->tf_rsp;
	mcp->mc_eflags = tp->tf_rflags;
	if (flags & GET_MC_CLEAR_RET) {
		mcp->mc_eax = 0;
		mcp->mc_edx = 0;
		mcp->mc_eflags &= ~PSL_C;
	} else {
		mcp->mc_eax = tp->tf_rax;
		mcp->mc_edx = tp->tf_rdx;
	}
	mcp->mc_ebx = tp->tf_rbx;
	mcp->mc_ecx = tp->tf_rcx;
	mcp->mc_eip = tp->tf_rip;
	mcp->mc_cs = tp->tf_cs;
	mcp->mc_esp = tp->tf_rsp;
	mcp->mc_ss = tp->tf_ss;
	mcp->mc_len = sizeof(*mcp);
	mcp->mc_flags = tp->tf_flags;
	ia32_get_fpcontext(td, mcp, NULL, 0);
	mcp->mc_fsbase = pcb->pcb_fsbase;
	mcp->mc_gsbase = pcb->pcb_gsbase;
	mcp->mc_xfpustate = 0;
	mcp->mc_xfpustate_len = 0;
	bzero(mcp->mc_spare2, sizeof(mcp->mc_spare2));
	return (0);
}