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
struct trapframe {int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_r15; int /*<<< orphan*/  tf_r14; int /*<<< orphan*/  tf_r13; int /*<<< orphan*/  tf_r12; } ;
struct pcb {int /*<<< orphan*/  pcb_rsp; int /*<<< orphan*/  pcb_rip; int /*<<< orphan*/  pcb_rbx; int /*<<< orphan*/  pcb_rbp; int /*<<< orphan*/  pcb_r15; int /*<<< orphan*/  pcb_r14; int /*<<< orphan*/  pcb_r13; int /*<<< orphan*/  pcb_r12; } ;

/* Variables and functions */

void
makectx(struct trapframe *tf, struct pcb *pcb)
{

	pcb->pcb_r12 = tf->tf_r12;
	pcb->pcb_r13 = tf->tf_r13;
	pcb->pcb_r14 = tf->tf_r14;
	pcb->pcb_r15 = tf->tf_r15;
	pcb->pcb_rbp = tf->tf_rbp;
	pcb->pcb_rbx = tf->tf_rbx;
	pcb->pcb_rip = tf->tf_rip;
	pcb->pcb_rsp = tf->tf_rsp;
}