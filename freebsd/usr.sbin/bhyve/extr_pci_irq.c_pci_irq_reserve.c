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
 scalar_t__ IRQ_DISABLED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* irq_counts ; 
 int nitems (scalar_t__*) ; 
 int pirq_cold ; 

void
pci_irq_reserve(int irq)
{

	assert(irq >= 0 && irq < nitems(irq_counts));
	assert(pirq_cold);
	assert(irq_counts[irq] == 0 || irq_counts[irq] == IRQ_DISABLED);
	irq_counts[irq] = IRQ_DISABLED;
}