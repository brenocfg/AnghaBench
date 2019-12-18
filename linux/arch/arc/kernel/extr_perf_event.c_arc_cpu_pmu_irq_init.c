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

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_PCT_INT_ACT ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  enable_percpu_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arc_cpu_pmu_irq_init(void *data)
{
	int irq = *(int *)data;

	enable_percpu_irq(irq, IRQ_TYPE_NONE);

	/* Clear all pending interrupt flags */
	write_aux_reg(ARC_REG_PCT_INT_ACT, 0xffffffff);
}