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
 int ADM5120_INTC_IRQ_BASE ; 
 unsigned long INTC_INT_ALL ; 
 int /*<<< orphan*/  INTC_REG_IRQ_STATUS ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int fls (unsigned long) ; 
 unsigned long intc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void adm5120_intc_irq_dispatch(void)
{
	unsigned long status;
	int irq;

	status = intc_read_reg(INTC_REG_IRQ_STATUS) & INTC_INT_ALL;
	if (status) {
		irq = ADM5120_INTC_IRQ_BASE + fls(status) - 1;
		do_IRQ(irq);
	} else
		spurious_interrupt();
}