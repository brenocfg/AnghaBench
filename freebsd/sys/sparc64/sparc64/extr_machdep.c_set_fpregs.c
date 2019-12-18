#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct trapframe {int /*<<< orphan*/  tf_gsr; int /*<<< orphan*/  tf_fsr; int /*<<< orphan*/  tf_fprs; } ;
struct thread {struct trapframe* td_frame; struct pcb* td_pcb; } ;
struct pcb {int /*<<< orphan*/  pcb_ufp; } ;
struct fpreg {int /*<<< orphan*/  fr_gsr; int /*<<< orphan*/  fr_fsr; int /*<<< orphan*/  fr_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPRS_FEF ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
set_fpregs(struct thread *td, struct fpreg *fpregs)
{
	struct trapframe *tf;
	struct pcb *pcb;

	pcb = td->td_pcb;
	tf = td->td_frame;
	tf->tf_fprs &= ~FPRS_FEF;
	bcopy(fpregs->fr_regs, pcb->pcb_ufp, sizeof(pcb->pcb_ufp));
	tf->tf_fsr = fpregs->fr_fsr;
	tf->tf_gsr = fpregs->fr_gsr;
	return (0);
}