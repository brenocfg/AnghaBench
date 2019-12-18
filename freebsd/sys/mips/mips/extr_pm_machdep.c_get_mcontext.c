#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; int /*<<< orphan*/  pc; int /*<<< orphan*/  f0; int /*<<< orphan*/  zero; int /*<<< orphan*/  sp; } ;
struct TYPE_5__ {int md_flags; int /*<<< orphan*/  md_tls; } ;
struct thread {TYPE_1__ td_md; struct trapframe* td_frame; } ;
struct TYPE_6__ {int mc_fpused; int /*<<< orphan*/  mc_tls; int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; int /*<<< orphan*/  mc_pc; scalar_t__* mc_regs; int /*<<< orphan*/  mc_fpregs; int /*<<< orphan*/  mc_onstack; } ;
typedef  TYPE_2__ mcontext_t ;
struct TYPE_7__ {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 size_t A3 ; 
 int GET_MC_CLEAR_RET ; 
 int MDTD_FPUSED ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 size_t V0 ; 
 size_t V1 ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 TYPE_4__* curthread ; 
 int /*<<< orphan*/  sigonstack (int /*<<< orphan*/ ) ; 

int
get_mcontext(struct thread *td, mcontext_t *mcp, int flags)
{
	struct trapframe *tp;

	tp = td->td_frame;
	PROC_LOCK(curthread->td_proc);
	mcp->mc_onstack = sigonstack(tp->sp);
	PROC_UNLOCK(curthread->td_proc);
	bcopy((void *)&td->td_frame->zero, (void *)&mcp->mc_regs,
	    sizeof(mcp->mc_regs));

	mcp->mc_fpused = td->td_md.md_flags & MDTD_FPUSED;
	if (mcp->mc_fpused) {
		bcopy((void *)&td->td_frame->f0, (void *)&mcp->mc_fpregs,
		    sizeof(mcp->mc_fpregs));
	}
	if (flags & GET_MC_CLEAR_RET) {
		mcp->mc_regs[V0] = 0;
		mcp->mc_regs[V1] = 0;
		mcp->mc_regs[A3] = 0;
	}

	mcp->mc_pc = td->td_frame->pc;
	mcp->mullo = td->td_frame->mullo;
	mcp->mulhi = td->td_frame->mulhi;
	mcp->mc_tls = td->td_md.md_tls;
	return (0);
}