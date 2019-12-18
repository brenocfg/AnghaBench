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
struct irq_data {unsigned int irq; } ;
struct TYPE_2__ {unsigned int fpgaIrq; int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  MICRODEV_FPGA_INTC_MASK (unsigned int) ; 
 int /*<<< orphan*/  MICRODEV_FPGA_INTDSB_REG ; 
 unsigned int NUM_EXTERNAL_IRQS ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* fpgaIrqTable ; 

__attribute__((used)) static void disable_microdev_irq(struct irq_data *data)
{
	unsigned int irq = data->irq;
	unsigned int fpgaIrq;

	if (irq >= NUM_EXTERNAL_IRQS)
		return;
	if (!fpgaIrqTable[irq].mapped)
		return;

	fpgaIrq = fpgaIrqTable[irq].fpgaIrq;

	/* disable interrupts on the FPGA INTC register */
	__raw_writel(MICRODEV_FPGA_INTC_MASK(fpgaIrq), MICRODEV_FPGA_INTDSB_REG);
}