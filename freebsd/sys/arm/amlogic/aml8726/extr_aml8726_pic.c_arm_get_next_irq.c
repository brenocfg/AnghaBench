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
typedef  int uint32_t ;

/* Variables and functions */
 int AML_PIC_BIT (int) ; 
 int AML_PIC_IRQS_PER_CNTRL ; 
 int AML_PIC_NIRQS ; 
 int /*<<< orphan*/  AML_PIC_STAT_REG (int) ; 
 int CSR_READ_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_pic_sc ; 

int
arm_get_next_irq(int last)
{
	uint32_t value;
	int irq;
	int start;

	/*
	 * The extra complexity is simply so that all IRQs are checked
	 * round robin so a particularly busy interrupt can't prevent
	 * other interrupts from being serviced.
	 */

	start = (last + 1) % AML_PIC_NIRQS;
	irq = start;

	for ( ; ; ) {
		value = CSR_READ_4(aml8726_pic_sc, AML_PIC_STAT_REG(irq));

		for ( ; ; ) {
			if ((value & AML_PIC_BIT(irq)) != 0)
				return (irq);

			irq = (irq + 1) % AML_PIC_NIRQS;

			if (irq == start)
				return (-1);

			if ((irq % AML_PIC_IRQS_PER_CNTRL) == 0)
				break;
		}
	}
}