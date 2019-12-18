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
typedef  int u32 ;
struct irq_data {unsigned int irq; } ;
struct TYPE_2__ {int index; int /*<<< orphan*/  icr; scalar_t__ ack; } ;

/* Variables and functions */
 unsigned int MCFINT_VECBASE ; 
 unsigned int MCFINT_VECMAX ; 
 TYPE_1__* intc_irqmap ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intc_irq_ack(struct irq_data *d)
{
	unsigned int irq = d->irq;

	/* Only external interrupts are acked */
	if ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX)) {
		irq -= MCFINT_VECBASE;
		if (intc_irqmap[irq].ack) {
			u32 v;
			v = readl(intc_irqmap[irq].icr);
			v &= (0x7 << intc_irqmap[irq].index);
			v |= (0x8 << intc_irqmap[irq].index);
			writel(v, intc_irqmap[irq].icr);
		}
	}
}