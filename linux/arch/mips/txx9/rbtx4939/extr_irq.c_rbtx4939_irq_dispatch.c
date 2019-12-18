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
 int CAUSEF_IP0 ; 
 int CAUSEF_IP1 ; 
 int CAUSEF_IP7 ; 
 int MIPS_CPU_IRQ_BASE ; 
#define  RBTX4939_IRQ_IOCINT 128 
 scalar_t__ likely (int) ; 
 int rbtx4939_ioc_irqroute () ; 
 int tx4939_irq () ; 

__attribute__((used)) static int rbtx4939_irq_dispatch(int pending)
{
	int irq;

	if (pending & CAUSEF_IP7)
		return MIPS_CPU_IRQ_BASE + 7;
	irq = tx4939_irq();
	if (likely(irq >= 0)) {
		/* redirect IOC interrupts */
		switch (irq) {
		case RBTX4939_IRQ_IOCINT:
			irq = rbtx4939_ioc_irqroute();
			break;
		}
	} else if (pending & CAUSEF_IP0)
		irq = MIPS_CPU_IRQ_BASE + 0;
	else if (pending & CAUSEF_IP1)
		irq = MIPS_CPU_IRQ_BASE + 1;
	else
		irq = -1;
	return irq;
}