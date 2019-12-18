#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; int /*<<< orphan*/  pc; int /*<<< orphan*/  f0; int /*<<< orphan*/  zero; } ;
struct TYPE_4__ {int md_flags; int /*<<< orphan*/  md_tls; } ;
struct thread {TYPE_1__ td_md; struct trapframe* td_frame; } ;
struct TYPE_5__ {int mc_fpused; int /*<<< orphan*/  mc_tls; int /*<<< orphan*/  mulhi; int /*<<< orphan*/  mullo; int /*<<< orphan*/  mc_pc; int /*<<< orphan*/  mc_fpregs; int /*<<< orphan*/  mc_regs; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */
 int MDTD_FPUSED ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 

int
set_mcontext(struct thread *td, mcontext_t *mcp)
{
	struct trapframe *tp;

	tp = td->td_frame;
	bcopy((void *)&mcp->mc_regs, (void *)&td->td_frame->zero,
	    sizeof(mcp->mc_regs));

	td->td_md.md_flags = mcp->mc_fpused & MDTD_FPUSED;
	if (mcp->mc_fpused) {
		bcopy((void *)&mcp->mc_fpregs, (void *)&td->td_frame->f0,
		    sizeof(mcp->mc_fpregs));
	}
	td->td_frame->pc = mcp->mc_pc;
	td->td_frame->mullo = mcp->mullo;
	td->td_frame->mulhi = mcp->mulhi;
	td->td_md.md_tls = mcp->mc_tls;
	/* Dont let user to set any bits in status and cause registers. */

	return (0);
}