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
struct trapframe {int /*<<< orphan*/  tf_gsr; int /*<<< orphan*/  tf_fsr; } ;
struct thread {struct trapframe* td_frame; struct pcb* td_pcb; } ;
struct pcb {int /*<<< orphan*/  pcb_ufp; } ;
struct fpreg {scalar_t__* fr_pad; int /*<<< orphan*/  fr_gsr; int /*<<< orphan*/  fr_fsr; int /*<<< orphan*/  fr_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
fill_fpregs(struct thread *td, struct fpreg *fpregs)
{
	struct trapframe *tf;
	struct pcb *pcb;

	pcb = td->td_pcb;
	tf = td->td_frame;
	bcopy(pcb->pcb_ufp, fpregs->fr_regs, sizeof(fpregs->fr_regs));
	fpregs->fr_fsr = tf->tf_fsr;
	fpregs->fr_gsr = tf->tf_gsr;
	fpregs->fr_pad[0] = 0;
	return (0);
}