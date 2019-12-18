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
struct pcb {TYPE_1__ pcb_fpustate; TYPE_1__* pcb_fpusaved; } ;
struct fpreg {int /*<<< orphan*/  fp_sr; int /*<<< orphan*/  fp_cr; int /*<<< orphan*/  fp_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
set_fpregs(struct thread *td, struct fpreg *regs)
{
#ifdef VFP
	struct pcb *pcb;

	pcb = td->td_pcb;
	KASSERT(pcb->pcb_fpusaved == &pcb->pcb_fpustate,
	    ("Called set_fpregs while the kernel is using the VFP"));
	memcpy(pcb->pcb_fpustate.vfp_regs, regs->fp_q, sizeof(regs->fp_q));
	pcb->pcb_fpustate.vfp_fpcr = regs->fp_cr;
	pcb->pcb_fpustate.vfp_fpsr = regs->fp_sr;
#endif
	return (0);
}