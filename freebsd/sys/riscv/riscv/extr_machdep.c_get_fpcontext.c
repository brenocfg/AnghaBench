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
struct thread {struct pcb* td_pcb; } ;
struct pcb {int pcb_fpflags; int /*<<< orphan*/  pcb_fcsr; int /*<<< orphan*/  pcb_x; } ;
struct TYPE_5__ {int fp_flags; int /*<<< orphan*/  fp_fcsr; int /*<<< orphan*/  fp_x; } ;
struct TYPE_6__ {int /*<<< orphan*/  mc_flags; TYPE_1__ mc_fpregs; } ;
typedef  TYPE_2__ mcontext_t ;
struct TYPE_7__ {struct pcb* td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCB_FP_STARTED ; 
 int PCB_FP_USERMASK ; 
 int /*<<< orphan*/  _MC_FP_VALID ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_4__* curthread ; 
 int /*<<< orphan*/  fpe_state_save (struct thread*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
get_fpcontext(struct thread *td, mcontext_t *mcp)
{
#ifdef FPE
	struct pcb *curpcb;

	critical_enter();

	curpcb = curthread->td_pcb;

	KASSERT(td->td_pcb == curpcb, ("Invalid fpe pcb"));

	if ((curpcb->pcb_fpflags & PCB_FP_STARTED) != 0) {
		/*
		 * If we have just been running FPE instructions we will
		 * need to save the state to memcpy it below.
		 */
		fpe_state_save(td);

		KASSERT((curpcb->pcb_fpflags & ~PCB_FP_USERMASK) == 0,
		    ("Non-userspace FPE flags set in get_fpcontext"));
		memcpy(mcp->mc_fpregs.fp_x, curpcb->pcb_x,
		    sizeof(mcp->mc_fpregs));
		mcp->mc_fpregs.fp_fcsr = curpcb->pcb_fcsr;
		mcp->mc_fpregs.fp_flags = curpcb->pcb_fpflags;
		mcp->mc_flags |= _MC_FP_VALID;
	}

	critical_exit();
#endif
}