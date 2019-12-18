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
struct INTENTRY {int int_flags; int dst_apic_id; int dst_apic_int; int src_bus_irq; void* int_type; scalar_t__ src_bus_id; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int config_type; } ;

/* Variables and functions */
 int INTENTRY_FLAGS_POLARITY_CONFORM ; 
 int INTENTRY_FLAGS_TRIGGER_CONFORM ; 
 void* INTENTRY_TYPE_EXTINT ; 
 void* INTENTRY_TYPE_INT ; 
 int /*<<< orphan*/  MPCT_ENTRY_INT ; 
 int /*<<< orphan*/  ioapic_disable_pin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ioapics ; 
 TYPE_1__* mpfps ; 
 int /*<<< orphan*/  mptable_parse_io_int (struct INTENTRY*) ; 

__attribute__((used)) static void
mptable_parse_default_config_ints(void)
{
	struct INTENTRY entry;
	int pin;

	/*
	 * All default configs route IRQs from bus 0 to the first 16 pins
	 * of the first I/O APIC with an APIC ID of 2.
	 */
	entry.type = MPCT_ENTRY_INT;
	entry.int_flags = INTENTRY_FLAGS_POLARITY_CONFORM |
	    INTENTRY_FLAGS_TRIGGER_CONFORM;
	entry.src_bus_id = 0;
	entry.dst_apic_id = 2;

	/* Run through all 16 pins. */
	for (pin = 0; pin < 16; pin++) {
		entry.dst_apic_int = pin;
		switch (pin) {
		case 0:
			/* Pin 0 is an ExtINT pin. */
			entry.int_type = INTENTRY_TYPE_EXTINT;
			break;
		case 2:
			/* IRQ 0 is routed to pin 2. */
			entry.int_type = INTENTRY_TYPE_INT;
			entry.src_bus_irq = 0;
			break;
		default:
			/* All other pins are identity mapped. */
			entry.int_type = INTENTRY_TYPE_INT;
			entry.src_bus_irq = pin;
			break;
		}
		mptable_parse_io_int(&entry);
	}

	/* Certain configs disable certain pins. */
	if (mpfps->config_type == 7)
		ioapic_disable_pin(ioapics[2], 0);
	if (mpfps->config_type == 2) {
		ioapic_disable_pin(ioapics[2], 2);
		ioapic_disable_pin(ioapics[2], 13);
	}
}