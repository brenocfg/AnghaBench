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
struct trapframe {int /*<<< orphan*/  tf_spsr; int /*<<< orphan*/  tf_pc; int /*<<< orphan*/  tf_usr_lr; int /*<<< orphan*/  tf_usr_sp; int /*<<< orphan*/  tf_r0; } ;
struct thread {struct trapframe* td_frame; } ;
struct reg {int /*<<< orphan*/  r_cpsr; int /*<<< orphan*/  r_pc; int /*<<< orphan*/  r_lr; int /*<<< orphan*/  r_sp; int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
fill_regs(struct thread *td, struct reg *regs)
{
	struct trapframe *tf = td->td_frame;
	bcopy(&tf->tf_r0, regs->r, sizeof(regs->r));
	regs->r_sp = tf->tf_usr_sp;
	regs->r_lr = tf->tf_usr_lr;
	regs->r_pc = tf->tf_pc;
	regs->r_cpsr = tf->tf_spsr;
	return (0);
}