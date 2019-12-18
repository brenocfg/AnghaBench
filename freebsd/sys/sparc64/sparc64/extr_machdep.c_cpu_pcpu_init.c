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
struct pcpu {struct intr_request* pc_irfree; struct intr_request* pc_irpool; int /*<<< orphan*/  pc_irhead; int /*<<< orphan*/ * pc_irtail; } ;
struct intr_request {struct intr_request* ir_next; } ;

/* Variables and functions */
 int IR_FREE ; 

void
cpu_pcpu_init(struct pcpu *pcpu, int cpuid, size_t size)
{
	struct intr_request *ir;
	int i;

	pcpu->pc_irtail = &pcpu->pc_irhead;
	for (i = 0; i < IR_FREE; i++) {
		ir = &pcpu->pc_irpool[i];
		ir->ir_next = pcpu->pc_irfree;
		pcpu->pc_irfree = ir;
	}
}