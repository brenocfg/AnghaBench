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
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int tf_pc; int /*<<< orphan*/  tf_r0; } ;
struct thread {scalar_t__ td_intr_nesting_level; TYPE_1__* td_pcb; } ;
struct ksig {int /*<<< orphan*/  addr; int /*<<< orphan*/  sig; int /*<<< orphan*/  code; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pcb_onfault; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADRALN ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int TRAPF_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  abort_fatal (struct trapframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,struct ksig*) ; 

__attribute__((used)) static int
abort_align(struct trapframe *tf, u_int idx, u_int fsr, u_int far,
    u_int prefetch, struct thread *td, struct ksig *ksig)
{
	bool usermode;

	usermode = TRAPF_USERMODE(tf);
	if (!usermode) {
		if (td->td_intr_nesting_level == 0 && td != NULL &&
		    td->td_pcb->pcb_onfault != NULL) {
			tf->tf_r0 = EFAULT;
			tf->tf_pc = (int)td->td_pcb->pcb_onfault;
			return (0);
		}
		abort_fatal(tf, idx, fsr, far, prefetch, td, ksig);
	}
	/* Deliver a bus error signal to the process */
	ksig->code = BUS_ADRALN;
	ksig->sig = SIGBUS;
	ksig->addr = far;
	return (1);
}