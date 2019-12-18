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
struct trapframe {int /*<<< orphan*/  tf_sepc; int /*<<< orphan*/  tf_tp; int /*<<< orphan*/  tf_gp; int /*<<< orphan*/  tf_sp; int /*<<< orphan*/  tf_ra; int /*<<< orphan*/  tf_a; int /*<<< orphan*/  tf_s; int /*<<< orphan*/  tf_t; } ;
struct pcb {int /*<<< orphan*/  pcb_sepc; int /*<<< orphan*/  pcb_tp; int /*<<< orphan*/  pcb_gp; int /*<<< orphan*/  pcb_sp; int /*<<< orphan*/  pcb_ra; int /*<<< orphan*/  pcb_a; int /*<<< orphan*/  pcb_s; int /*<<< orphan*/  pcb_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
makectx(struct trapframe *tf, struct pcb *pcb)
{

	memcpy(pcb->pcb_t, tf->tf_t, sizeof(tf->tf_t));
	memcpy(pcb->pcb_s, tf->tf_s, sizeof(tf->tf_s));
	memcpy(pcb->pcb_a, tf->tf_a, sizeof(tf->tf_a));

	pcb->pcb_ra = tf->tf_ra;
	pcb->pcb_sp = tf->tf_sp;
	pcb->pcb_gp = tf->tf_gp;
	pcb->pcb_tp = tf->tf_tp;
	pcb->pcb_sepc = tf->tf_sepc;
}