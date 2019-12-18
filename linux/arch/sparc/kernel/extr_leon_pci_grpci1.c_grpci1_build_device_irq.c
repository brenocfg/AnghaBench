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
 int /*<<< orphan*/  grpci1_irq ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 unsigned int irq_alloc (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,void*) ; 

__attribute__((used)) static unsigned int grpci1_build_device_irq(unsigned int irq)
{
	unsigned int virq = 0, pil;

	pil = 1 << 8;
	virq = irq_alloc(irq, pil);
	if (virq == 0)
		goto out;

	irq_set_chip_and_handler_name(virq, &grpci1_irq, handle_simple_irq,
				      "pcilvl");
	irq_set_chip_data(virq, (void *)irq);

out:
	return virq;
}