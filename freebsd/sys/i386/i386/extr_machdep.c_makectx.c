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
struct trapframe {int tf_esp; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_eip; int /*<<< orphan*/  tf_ebx; int /*<<< orphan*/  tf_ebp; int /*<<< orphan*/  tf_esi; int /*<<< orphan*/  tf_edi; } ;
struct pcb {int pcb_esp; int /*<<< orphan*/  pcb_gs; int /*<<< orphan*/  pcb_eip; int /*<<< orphan*/  pcb_ebx; int /*<<< orphan*/  pcb_ebp; int /*<<< orphan*/  pcb_esi; int /*<<< orphan*/  pcb_edi; } ;

/* Variables and functions */
 scalar_t__ ISPL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgs () ; 

void
makectx(struct trapframe *tf, struct pcb *pcb)
{

	pcb->pcb_edi = tf->tf_edi;
	pcb->pcb_esi = tf->tf_esi;
	pcb->pcb_ebp = tf->tf_ebp;
	pcb->pcb_ebx = tf->tf_ebx;
	pcb->pcb_eip = tf->tf_eip;
	pcb->pcb_esp = (ISPL(tf->tf_cs)) ? tf->tf_esp : (int)(tf + 1) - 8;
	pcb->pcb_gs = rgs();
}