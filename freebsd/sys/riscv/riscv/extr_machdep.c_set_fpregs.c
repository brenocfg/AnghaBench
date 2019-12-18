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
struct trapframe {int /*<<< orphan*/  tf_sstatus; } ;
struct thread {struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct pcb {int /*<<< orphan*/  pcb_fpflags; int /*<<< orphan*/  pcb_fcsr; int /*<<< orphan*/  pcb_x; } ;
struct fpreg {int /*<<< orphan*/  fp_fcsr; int /*<<< orphan*/  fp_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_FP_STARTED ; 
 int /*<<< orphan*/  SSTATUS_FS_CLEAN ; 
 int /*<<< orphan*/  SSTATUS_FS_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
set_fpregs(struct thread *td, struct fpreg *regs)
{
#ifdef FPE
	struct trapframe *frame;
	struct pcb *pcb;

	frame = td->td_frame;
	pcb = td->td_pcb;

	memcpy(pcb->pcb_x, regs->fp_x, sizeof(regs->fp_x));
	pcb->pcb_fcsr = regs->fp_fcsr;
	pcb->pcb_fpflags |= PCB_FP_STARTED;
	frame->tf_sstatus &= ~SSTATUS_FS_MASK;
	frame->tf_sstatus |= SSTATUS_FS_CLEAN;
#endif

	return (0);
}