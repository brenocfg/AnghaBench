#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rflags; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_r11; int /*<<< orphan*/  tf_r12; int /*<<< orphan*/  tf_r13; int /*<<< orphan*/  tf_r14; int /*<<< orphan*/  tf_r15; } ;
struct thread {struct trapframe* td_frame; struct pcb* td_pcb; } ;
struct pcb {int /*<<< orphan*/  pcb_gsbase; int /*<<< orphan*/  pcb_fsbase; } ;
struct TYPE_5__ {int mc_len; int /*<<< orphan*/  mc_spare; scalar_t__ mc_xfpustate_len; scalar_t__ mc_xfpustate; int /*<<< orphan*/  mc_gsbase; int /*<<< orphan*/  mc_fsbase; int /*<<< orphan*/  mc_flags; int /*<<< orphan*/  mc_gs; int /*<<< orphan*/  mc_fs; int /*<<< orphan*/  mc_es; int /*<<< orphan*/  mc_ds; int /*<<< orphan*/  mc_ss; int /*<<< orphan*/  mc_rsp; int /*<<< orphan*/  mc_cs; int /*<<< orphan*/  mc_rip; int /*<<< orphan*/  mc_rdx; int /*<<< orphan*/  mc_rax; int /*<<< orphan*/  mc_rflags; int /*<<< orphan*/  mc_rcx; int /*<<< orphan*/  mc_rbx; int /*<<< orphan*/  mc_rbp; int /*<<< orphan*/  mc_rsi; int /*<<< orphan*/  mc_rdi; int /*<<< orphan*/  mc_r8; int /*<<< orphan*/  mc_r9; int /*<<< orphan*/  mc_r10; int /*<<< orphan*/  mc_r11; int /*<<< orphan*/  mc_r12; int /*<<< orphan*/  mc_r13; int /*<<< orphan*/  mc_r14; int /*<<< orphan*/  mc_r15; int /*<<< orphan*/  mc_onstack; } ;
typedef  TYPE_1__ mcontext_t ;
struct TYPE_6__ {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int GET_MC_CLEAR_RET ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSL_C ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* curthread ; 
 int /*<<< orphan*/  get_fpcontext (struct thread*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigonstack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_pcb_bases (struct pcb*) ; 

int
get_mcontext(struct thread *td, mcontext_t *mcp, int flags)
{
	struct pcb *pcb;
	struct trapframe *tp;

	pcb = td->td_pcb;
	tp = td->td_frame;
	PROC_LOCK(curthread->td_proc);
	mcp->mc_onstack = sigonstack(tp->tf_rsp);
	PROC_UNLOCK(curthread->td_proc);
	mcp->mc_r15 = tp->tf_r15;
	mcp->mc_r14 = tp->tf_r14;
	mcp->mc_r13 = tp->tf_r13;
	mcp->mc_r12 = tp->tf_r12;
	mcp->mc_r11 = tp->tf_r11;
	mcp->mc_r10 = tp->tf_r10;
	mcp->mc_r9  = tp->tf_r9;
	mcp->mc_r8  = tp->tf_r8;
	mcp->mc_rdi = tp->tf_rdi;
	mcp->mc_rsi = tp->tf_rsi;
	mcp->mc_rbp = tp->tf_rbp;
	mcp->mc_rbx = tp->tf_rbx;
	mcp->mc_rcx = tp->tf_rcx;
	mcp->mc_rflags = tp->tf_rflags;
	if (flags & GET_MC_CLEAR_RET) {
		mcp->mc_rax = 0;
		mcp->mc_rdx = 0;
		mcp->mc_rflags &= ~PSL_C;
	} else {
		mcp->mc_rax = tp->tf_rax;
		mcp->mc_rdx = tp->tf_rdx;
	}
	mcp->mc_rip = tp->tf_rip;
	mcp->mc_cs = tp->tf_cs;
	mcp->mc_rsp = tp->tf_rsp;
	mcp->mc_ss = tp->tf_ss;
	mcp->mc_ds = tp->tf_ds;
	mcp->mc_es = tp->tf_es;
	mcp->mc_fs = tp->tf_fs;
	mcp->mc_gs = tp->tf_gs;
	mcp->mc_flags = tp->tf_flags;
	mcp->mc_len = sizeof(*mcp);
	get_fpcontext(td, mcp, NULL, 0);
	update_pcb_bases(pcb);
	mcp->mc_fsbase = pcb->pcb_fsbase;
	mcp->mc_gsbase = pcb->pcb_gsbase;
	mcp->mc_xfpustate = 0;
	mcp->mc_xfpustate_len = 0;
	bzero(mcp->mc_spare, sizeof(mcp->mc_spare));
	return (0);
}