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
struct trapframe {int /*<<< orphan*/  tf_spsr; int /*<<< orphan*/  tf_elr; scalar_t__* tf_x; } ;
struct thread {struct trapframe* td_frame; } ;
struct image_params {int /*<<< orphan*/  entry_addr; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  cloudabi32_tcb_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_AARCH32 ; 
 scalar_t__ STACKALIGN (unsigned long) ; 
 int /*<<< orphan*/  TO_PTR (unsigned long) ; 
 int /*<<< orphan*/  cpu_set_user_tls (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct trapframe*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ roundup (int,int) ; 

__attribute__((used)) static void
cloudabi32_proc_setregs(struct thread *td, struct image_params *imgp,
    unsigned long stack)
{
	struct trapframe *regs;

	regs = td->td_frame;
	memset(regs, 0, sizeof(*regs));
	regs->tf_x[0] =
	    stack + roundup(sizeof(cloudabi32_tcb_t), sizeof(register_t));
	regs->tf_x[13] = STACKALIGN(stack);
	regs->tf_elr = imgp->entry_addr;
	regs->tf_spsr |= PSR_AARCH32;
	(void)cpu_set_user_tls(td, TO_PTR(stack));
}