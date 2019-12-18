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
struct TYPE_2__ {scalar_t__ trigger; scalar_t__ polarity; } ;
struct mp_chip_data {int count; scalar_t__ trigger; scalar_t__ polarity; TYPE_1__ entry; } ;
struct irq_alloc_info {scalar_t__ ioapic_trigger; scalar_t__ ioapic_polarity; } ;

/* Variables and functions */
 struct mp_chip_data* irq_get_chip_data (int) ; 
 int /*<<< orphan*/  mp_register_handler (int,scalar_t__) ; 
 int nr_legacy_irqs () ; 

__attribute__((used)) static bool mp_check_pin_attr(int irq, struct irq_alloc_info *info)
{
	struct mp_chip_data *data = irq_get_chip_data(irq);

	/*
	 * setup_IO_APIC_irqs() programs all legacy IRQs with default trigger
	 * and polarity attirbutes. So allow the first user to reprogram the
	 * pin with real trigger and polarity attributes.
	 */
	if (irq < nr_legacy_irqs() && data->count == 1) {
		if (info->ioapic_trigger != data->trigger)
			mp_register_handler(irq, info->ioapic_trigger);
		data->entry.trigger = data->trigger = info->ioapic_trigger;
		data->entry.polarity = data->polarity = info->ioapic_polarity;
	}

	return data->trigger == info->ioapic_trigger &&
	       data->polarity == info->ioapic_polarity;
}