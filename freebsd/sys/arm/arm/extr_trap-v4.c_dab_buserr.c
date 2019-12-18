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
typedef  int u_int ;
struct trapframe {int tf_spsr; scalar_t__ tf_pc; int /*<<< orphan*/  tf_r0; scalar_t__ tf_usr_lr; } ;
struct thread {struct trapframe* td_frame; struct pcb* td_pcb; } ;
struct TYPE_2__ {scalar_t__ sf_sp; } ;
struct pcb {int /*<<< orphan*/ * pcb_onfault; TYPE_1__ pcb_regs; } ;
struct ksig {scalar_t__ code; int /*<<< orphan*/  signb; } ;
typedef  scalar_t__ register_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int FAULT_IMPRECISE ; 
 int PSR_ABT32_MODE ; 
 int PSR_MODE ; 
 int PSR_SVC32_MODE ; 
 int PSR_USR32_MODE ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  TRAP_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  dab_fatal (struct trapframe*,int,int,struct thread*,struct ksig*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
dab_buserr(struct trapframe *tf, u_int fsr, u_int far, struct thread *td,
    struct ksig *ksig)
{
	struct pcb *pcb = td->td_pcb;

#ifdef __XSCALE__
	if ((fsr & FAULT_IMPRECISE) != 0 &&
	    (tf->tf_spsr & PSR_MODE) == PSR_ABT32_MODE) {
		/*
		 * Oops, an imprecise, double abort fault. We've lost the
		 * r14_abt/spsr_abt values corresponding to the original
		 * abort, and the spsr saved in the trapframe indicates
		 * ABT mode.
		 */
		tf->tf_spsr &= ~PSR_MODE;

		/*
		 * We use a simple heuristic to determine if the double abort
		 * happened as a result of a kernel or user mode access.
		 * If the current trapframe is at the top of the kernel stack,
		 * the fault _must_ have come from user mode.
		 */
		if (tf != ((struct trapframe *)pcb->pcb_regs.sf_sp) - 1) {
			/*
			 * Kernel mode. We're either about to die a
			 * spectacular death, or pcb_onfault will come
			 * to our rescue. Either way, the current value
			 * of tf->tf_pc is irrelevant.
			 */
			tf->tf_spsr |= PSR_SVC32_MODE;
			if (pcb->pcb_onfault == NULL)
				printf("\nKernel mode double abort!\n");
		} else {
			/*
			 * User mode. We've lost the program counter at the
			 * time of the fault (not that it was accurate anyway;
			 * it's not called an imprecise fault for nothing).
			 * About all we can do is copy r14_usr to tf_pc and
			 * hope for the best. The process is about to get a
			 * SIGBUS, so it's probably history anyway.
			 */
			tf->tf_spsr |= PSR_USR32_MODE;
			tf->tf_pc = tf->tf_usr_lr;
		}
	}

	/* FAR is invalid for imprecise exceptions */
	if ((fsr & FAULT_IMPRECISE) != 0)
		far = 0;
#endif /* __XSCALE__ */

	if (pcb->pcb_onfault) {
		tf->tf_r0 = EFAULT;
		tf->tf_pc = (register_t)(intptr_t) pcb->pcb_onfault;
		return (0);
	}

	/*
	 * At this point, if the fault happened in kernel mode, we're toast
	 */
	if (!TRAP_USERMODE(tf))
		dab_fatal(tf, fsr, far, td, ksig);

	/* Deliver a bus error signal to the process */
	ksig->signb = SIGBUS;
	ksig->code = 0;
	td->td_frame = tf;

	return (1);
}