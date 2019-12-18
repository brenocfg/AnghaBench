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
struct trapframe {int /*<<< orphan*/  tf_usr_sp; int /*<<< orphan*/  tf_usr_lr; int /*<<< orphan*/  tf_pc; int /*<<< orphan*/  tf_r12; int /*<<< orphan*/  tf_r11; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_r7; int /*<<< orphan*/  tf_r6; int /*<<< orphan*/  tf_r5; int /*<<< orphan*/  tf_r4; } ;
struct TYPE_2__ {int /*<<< orphan*/  sf_sp; int /*<<< orphan*/  sf_lr; int /*<<< orphan*/  sf_pc; int /*<<< orphan*/  sf_r12; int /*<<< orphan*/  sf_r11; int /*<<< orphan*/  sf_r10; int /*<<< orphan*/  sf_r9; int /*<<< orphan*/  sf_r8; int /*<<< orphan*/  sf_r7; int /*<<< orphan*/  sf_r6; int /*<<< orphan*/  sf_r5; int /*<<< orphan*/  sf_r4; } ;
struct pcb {TYPE_1__ pcb_regs; } ;

/* Variables and functions */

void
makectx(struct trapframe *tf, struct pcb *pcb)
{
	pcb->pcb_regs.sf_r4 = tf->tf_r4;
	pcb->pcb_regs.sf_r5 = tf->tf_r5;
	pcb->pcb_regs.sf_r6 = tf->tf_r6;
	pcb->pcb_regs.sf_r7 = tf->tf_r7;
	pcb->pcb_regs.sf_r8 = tf->tf_r8;
	pcb->pcb_regs.sf_r9 = tf->tf_r9;
	pcb->pcb_regs.sf_r10 = tf->tf_r10;
	pcb->pcb_regs.sf_r11 = tf->tf_r11;
	pcb->pcb_regs.sf_r12 = tf->tf_r12;
	pcb->pcb_regs.sf_pc = tf->tf_pc;
	pcb->pcb_regs.sf_lr = tf->tf_usr_lr;
	pcb->pcb_regs.sf_sp = tf->tf_usr_sp;
}