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
typedef  int /*<<< orphan*/  u32 ;
struct irq_alloc_info {int ioapic_pin; int ioapic_valid; int ioapic_trigger; int ioapic_polarity; int /*<<< orphan*/  ioapic_node; int /*<<< orphan*/  ioapic_id; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int IOAPIC_LEVEL ; 
 int IOAPIC_POL_LOW ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  X86_IRQ_ALLOC_TYPE_IOAPIC ; 
 scalar_t__ acpi_get_override_irq (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  copy_irq_alloc_info (struct irq_alloc_info*,struct irq_alloc_info*) ; 
 int /*<<< orphan*/  mpc_ioapic_id (int) ; 

__attribute__((used)) static void ioapic_copy_alloc_attr(struct irq_alloc_info *dst,
				   struct irq_alloc_info *src,
				   u32 gsi, int ioapic_idx, int pin)
{
	int trigger, polarity;

	copy_irq_alloc_info(dst, src);
	dst->type = X86_IRQ_ALLOC_TYPE_IOAPIC;
	dst->ioapic_id = mpc_ioapic_id(ioapic_idx);
	dst->ioapic_pin = pin;
	dst->ioapic_valid = 1;
	if (src && src->ioapic_valid) {
		dst->ioapic_node = src->ioapic_node;
		dst->ioapic_trigger = src->ioapic_trigger;
		dst->ioapic_polarity = src->ioapic_polarity;
	} else {
		dst->ioapic_node = NUMA_NO_NODE;
		if (acpi_get_override_irq(gsi, &trigger, &polarity) >= 0) {
			dst->ioapic_trigger = trigger;
			dst->ioapic_polarity = polarity;
		} else {
			/*
			 * PCI interrupts are always active low level
			 * triggered.
			 */
			dst->ioapic_trigger = IOAPIC_LEVEL;
			dst->ioapic_polarity = IOAPIC_POL_LOW;
		}
	}
}