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
typedef  int u32 ;

/* Variables and functions */
 int IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_STATUS_REG ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int fls (int) ; 
 int intc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void adm8668_irq_cascade(void)
{
	int irq;
	u32 intsrc;

	intsrc = intc_read_reg(IRQ_STATUS_REG) & IRQ_MASK;
	if (intsrc) {
		irq = fls(intsrc) - 1;
		do_IRQ(irq);
	} else
		spurious_interrupt();
}