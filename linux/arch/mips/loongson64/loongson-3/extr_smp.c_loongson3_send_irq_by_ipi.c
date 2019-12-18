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
 int IPI_IRQ_OFFSET ; 
 size_t cpu_logical_map (int) ; 
 int /*<<< orphan*/ * ipi_set0_regs ; 
 int /*<<< orphan*/  loongson3_ipi_write32 (int,int /*<<< orphan*/ ) ; 

void loongson3_send_irq_by_ipi(int cpu, int irqs)
{
	loongson3_ipi_write32(irqs << IPI_IRQ_OFFSET, ipi_set0_regs[cpu_logical_map(cpu)]);
}