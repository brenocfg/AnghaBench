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
struct trapframe {int /*<<< orphan*/  sp; int /*<<< orphan*/  pc; int /*<<< orphan*/  ra; } ;
struct pcb {int /*<<< orphan*/ * pcb_context; } ;

/* Variables and functions */
 size_t PCB_REG_PC ; 
 size_t PCB_REG_RA ; 
 size_t PCB_REG_SP ; 

void
makectx(struct trapframe *tf, struct pcb *pcb)
{

	pcb->pcb_context[PCB_REG_RA] = tf->ra;
	pcb->pcb_context[PCB_REG_PC] = tf->pc;
	pcb->pcb_context[PCB_REG_SP] = tf->sp;
}