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
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;
struct mp_chip_data {TYPE_1__ entry; } ;
struct irq_data {struct mp_chip_data* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  apic_ack_irq (struct irq_data*) ; 
 int /*<<< orphan*/  eoi_ioapic_pin (int /*<<< orphan*/ ,struct mp_chip_data*) ; 

__attribute__((used)) static void ioapic_ir_ack_level(struct irq_data *irq_data)
{
	struct mp_chip_data *data = irq_data->chip_data;

	/*
	 * Intr-remapping uses pin number as the virtual vector
	 * in the RTE. Actual vector is programmed in
	 * intr-remapping table entry. Hence for the io-apic
	 * EOI we use the pin number.
	 */
	apic_ack_irq(irq_data);
	eoi_ioapic_pin(data->entry.vector, data);
}