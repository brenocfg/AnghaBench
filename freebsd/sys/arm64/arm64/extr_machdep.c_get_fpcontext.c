#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vfp_fpsr; int /*<<< orphan*/  vfp_fpcr; int /*<<< orphan*/  vfp_regs; } ;
struct pcb {int pcb_fpflags; TYPE_1__ pcb_fpustate; TYPE_1__* pcb_fpusaved; } ;
struct TYPE_7__ {int fp_flags; int /*<<< orphan*/  fp_sr; int /*<<< orphan*/  fp_cr; int /*<<< orphan*/  fp_q; } ;
struct TYPE_8__ {int /*<<< orphan*/  mc_flags; TYPE_2__ mc_fpregs; } ;
typedef  TYPE_3__ mcontext_t ;
struct TYPE_9__ {struct pcb* td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCB_FP_STARTED ; 
 int PCB_FP_USERMASK ; 
 int /*<<< orphan*/  _MC_FP_VALID ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfp_save_state (struct thread*,struct pcb*) ; 

__attribute__((used)) static void
get_fpcontext(struct thread *td, mcontext_t *mcp)
{
#ifdef VFP
	struct pcb *curpcb;

	critical_enter();

	curpcb = curthread->td_pcb;

	if ((curpcb->pcb_fpflags & PCB_FP_STARTED) != 0) {
		/*
		 * If we have just been running VFP instructions we will
		 * need to save the state to memcpy it below.
		 */
		vfp_save_state(td, curpcb);

		KASSERT(curpcb->pcb_fpusaved == &curpcb->pcb_fpustate,
		    ("Called get_fpcontext while the kernel is using the VFP"));
		KASSERT((curpcb->pcb_fpflags & ~PCB_FP_USERMASK) == 0,
		    ("Non-userspace FPU flags set in get_fpcontext"));
		memcpy(mcp->mc_fpregs.fp_q, curpcb->pcb_fpustate.vfp_regs,
		    sizeof(mcp->mc_fpregs));
		mcp->mc_fpregs.fp_cr = curpcb->pcb_fpustate.vfp_fpcr;
		mcp->mc_fpregs.fp_sr = curpcb->pcb_fpustate.vfp_fpsr;
		mcp->mc_fpregs.fp_flags = curpcb->pcb_fpflags;
		mcp->mc_flags |= _MC_FP_VALID;
	}

	critical_exit();
#endif
}