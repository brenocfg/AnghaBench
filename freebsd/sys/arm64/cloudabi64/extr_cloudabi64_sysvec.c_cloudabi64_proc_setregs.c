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
struct trapframe {scalar_t__* tf_x; } ;
struct thread {struct trapframe* td_frame; } ;
struct image_params {int dummy; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  cloudabi64_tcb_t ;

/* Variables and functions */
 int /*<<< orphan*/  TO_PTR (unsigned long) ; 
 int /*<<< orphan*/  cpu_set_user_tls (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_setregs (struct thread*,struct image_params*,unsigned long) ; 
 scalar_t__ roundup (int,int) ; 

__attribute__((used)) static void
cloudabi64_proc_setregs(struct thread *td, struct image_params *imgp,
    unsigned long stack)
{
	struct trapframe *regs;

	exec_setregs(td, imgp, stack);

	/*
	 * The stack now contains a pointer to the TCB and the auxiliary
	 * vector. Let x0 point to the auxiliary vector, and set
	 * tpidr_el0 to the TCB.
	 */
	regs = td->td_frame;
	regs->tf_x[0] =
	    stack + roundup(sizeof(cloudabi64_tcb_t), sizeof(register_t));
	(void)cpu_set_user_tls(td, TO_PTR(stack));
}