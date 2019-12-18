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
struct thread {struct pcb* td_pcb; } ;
struct pcb {int pcb_fpflags; int /*<<< orphan*/  pcb_fcsr; int /*<<< orphan*/  pcb_x; } ;
struct fpreg {int /*<<< orphan*/  fp_fcsr; int /*<<< orphan*/  fp_x; } ;

/* Variables and functions */
 int PCB_FP_STARTED ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fpe_state_save (struct thread*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fpreg*,int /*<<< orphan*/ ,int) ; 

int
fill_fpregs(struct thread *td, struct fpreg *regs)
{
#ifdef FPE
	struct pcb *pcb;

	pcb = td->td_pcb;

	if ((pcb->pcb_fpflags & PCB_FP_STARTED) != 0) {
		/*
		 * If we have just been running FPE instructions we will
		 * need to save the state to memcpy it below.
		 */
		if (td == curthread)
			fpe_state_save(td);

		memcpy(regs->fp_x, pcb->pcb_x, sizeof(regs->fp_x));
		regs->fp_fcsr = pcb->pcb_fcsr;
	} else
#endif
		memset(regs, 0, sizeof(*regs));

	return (0);
}