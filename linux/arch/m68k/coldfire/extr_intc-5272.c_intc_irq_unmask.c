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
struct TYPE_2__ {int index; int /*<<< orphan*/  icr; } ;

/* Variables and functions */
 unsigned int MCFINT_VECBASE ; 
 unsigned int MCFINT_VECMAX ; 
 TYPE_1__* intc_irqmap ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intc_irq_unmask(struct irq_data *d)
{
	unsigned int irq = d->irq;

	if ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECMAX)) {
		u32 v;
		irq -= MCFINT_VECBASE;
		v = 0xd << intc_irqmap[irq].index;
		writel(v, intc_irqmap[irq].icr);
	}
}