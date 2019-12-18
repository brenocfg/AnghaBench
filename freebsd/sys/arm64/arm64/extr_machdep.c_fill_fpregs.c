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
struct thread {struct pcb* td_pcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  vfp_fpsr; int /*<<< orphan*/  vfp_fpcr; int /*<<< orphan*/  vfp_regs; } ;
struct pcb {int pcb_fpflags; TYPE_1__ pcb_fpustate; TYPE_1__* pcb_fpusaved; } ;
struct fpreg {int /*<<< orphan*/  fp_sr; int /*<<< orphan*/  fp_cr; int /*<<< orphan*/  fp_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCB_FP_STARTED ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fpreg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfp_save_state (struct thread*,struct pcb*) ; 

int
fill_fpregs(struct thread *td, struct fpreg *regs)
{
#ifdef VFP
	struct pcb *pcb;

	pcb = td->td_pcb;
	if ((pcb->pcb_fpflags & PCB_FP_STARTED) != 0) {
		/*
		 * If we have just been running VFP instructions we will
		 * need to save the state to memcpy it below.
		 */
		if (td == curthread)
			vfp_save_state(td, pcb);

		KASSERT(pcb->pcb_fpusaved == &pcb->pcb_fpustate,
		    ("Called fill_fpregs while the kernel is using the VFP"));
		memcpy(regs->fp_q, pcb->pcb_fpustate.vfp_regs,
		    sizeof(regs->fp_q));
		regs->fp_cr = pcb->pcb_fpustate.vfp_fpcr;
		regs->fp_sr = pcb->pcb_fpustate.vfp_fpsr;
	} else
#endif
		memset(regs, 0, sizeof(*regs));
	return (0);
}