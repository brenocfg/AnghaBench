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
struct thread {struct trapframe* td_frame; TYPE_1__* td_pcb; } ;
struct ksig {int /*<<< orphan*/  signb; scalar_t__ code; } ;
struct TYPE_2__ {scalar_t__ pcb_onfault; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  TRAP_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  dab_fatal (struct trapframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,struct ksig*) ; 

__attribute__((used)) static int
dab_align(struct trapframe *tf, u_int fsr, u_int far, struct thread *td,
    struct ksig *ksig)
{

	/* Alignment faults are always fatal if they occur in kernel mode */
	if (!TRAP_USERMODE(tf)) {
		if (!td || !td->td_pcb->pcb_onfault)
			dab_fatal(tf, fsr, far, td, ksig);
		tf->tf_r0 = EFAULT;
		tf->tf_pc = (int)td->td_pcb->pcb_onfault;
		return (0);
	}

	/* pcb_onfault *must* be NULL at this point */

	/* Deliver a bus error signal to the process */
	ksig->code = 0;
	ksig->signb = SIGBUS;
	td->td_frame = tf;

	return (1);
}