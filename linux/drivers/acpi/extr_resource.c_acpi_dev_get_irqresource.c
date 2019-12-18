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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct resource {int start; int end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ACPI_ACTIVE_HIGH ; 
 scalar_t__ ACPI_ACTIVE_LOW ; 
 scalar_t__ ACPI_EDGE_SENSITIVE ; 
 scalar_t__ ACPI_LEVEL_SENSITIVE ; 
 int /*<<< orphan*/  acpi_dev_irq_flags (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  acpi_dev_irqresource_disabled (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_override_irq (int /*<<< orphan*/ ,int*,int*) ; 
 int acpi_register_gsi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  valid_IRQ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_dev_get_irqresource(struct resource *res, u32 gsi,
				     u8 triggering, u8 polarity, u8 shareable,
				     bool legacy)
{
	int irq, p, t;

	if (!valid_IRQ(gsi)) {
		acpi_dev_irqresource_disabled(res, gsi);
		return;
	}

	/*
	 * In IO-APIC mode, use overridden attribute. Two reasons:
	 * 1. BIOS bug in DSDT
	 * 2. BIOS uses IO-APIC mode Interrupt Source Override
	 *
	 * We do this only if we are dealing with IRQ() or IRQNoFlags()
	 * resource (the legacy ISA resources). With modern ACPI 5 devices
	 * using extended IRQ descriptors we take the IRQ configuration
	 * from _CRS directly.
	 */
	if (legacy && !acpi_get_override_irq(gsi, &t, &p)) {
		u8 trig = t ? ACPI_LEVEL_SENSITIVE : ACPI_EDGE_SENSITIVE;
		u8 pol = p ? ACPI_ACTIVE_LOW : ACPI_ACTIVE_HIGH;

		if (triggering != trig || polarity != pol) {
			pr_warning("ACPI: IRQ %d override to %s, %s\n", gsi,
				   t ? "level" : "edge", p ? "low" : "high");
			triggering = trig;
			polarity = pol;
		}
	}

	res->flags = acpi_dev_irq_flags(triggering, polarity, shareable);
	irq = acpi_register_gsi(NULL, gsi, triggering, polarity);
	if (irq >= 0) {
		res->start = irq;
		res->end = irq;
	} else {
		acpi_dev_irqresource_disabled(res, gsi);
	}
}