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
struct trapframe {int /*<<< orphan*/  tf_sp; int /*<<< orphan*/  tf_elr; int /*<<< orphan*/  tf_lr; int /*<<< orphan*/ * tf_x; } ;
struct pcb {int /*<<< orphan*/  pcb_sp; int /*<<< orphan*/  pcb_pc; int /*<<< orphan*/ * pcb_x; } ;

/* Variables and functions */
 int PCB_LR ; 

void
makectx(struct trapframe *tf, struct pcb *pcb)
{
	int i;

	for (i = 0; i < PCB_LR; i++)
		pcb->pcb_x[i] = tf->tf_x[i];

	pcb->pcb_x[PCB_LR] = tf->tf_lr;
	pcb->pcb_pc = tf->tf_elr;
	pcb->pcb_sp = tf->tf_sp;
}