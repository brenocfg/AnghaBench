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
struct mp_chip_data {int isa_irq; } ;
struct irq_domain {int dummy; } ;
struct irq_data {struct mp_chip_data* chip_data; scalar_t__ parent_data; } ;
struct irq_alloc_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  ioapic_pin; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  X86_IRQ_ALLOC_LEGACY ; 
 scalar_t__ __add_pin_to_irq_node (struct mp_chip_data*,int,int,int /*<<< orphan*/ ) ; 
 int __irq_domain_alloc_irqs (struct irq_domain*,int,int,int,struct irq_alloc_info*,int,int /*<<< orphan*/ *) ; 
 int ioapic_alloc_attr_node (struct irq_alloc_info*) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,int) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 int /*<<< orphan*/  mp_check_pin_attr (int,struct irq_alloc_info*) ; 

__attribute__((used)) static int alloc_isa_irq_from_domain(struct irq_domain *domain,
				     int irq, int ioapic, int pin,
				     struct irq_alloc_info *info)
{
	struct mp_chip_data *data;
	struct irq_data *irq_data = irq_get_irq_data(irq);
	int node = ioapic_alloc_attr_node(info);

	/*
	 * Legacy ISA IRQ has already been allocated, just add pin to
	 * the pin list assoicated with this IRQ and program the IOAPIC
	 * entry. The IOAPIC entry
	 */
	if (irq_data && irq_data->parent_data) {
		if (!mp_check_pin_attr(irq, info))
			return -EBUSY;
		if (__add_pin_to_irq_node(irq_data->chip_data, node, ioapic,
					  info->ioapic_pin))
			return -ENOMEM;
	} else {
		info->flags |= X86_IRQ_ALLOC_LEGACY;
		irq = __irq_domain_alloc_irqs(domain, irq, 1, node, info, true,
					      NULL);
		if (irq >= 0) {
			irq_data = irq_domain_get_irq_data(domain, irq);
			data = irq_data->chip_data;
			data->isa_irq = true;
		}
	}

	return irq;
}