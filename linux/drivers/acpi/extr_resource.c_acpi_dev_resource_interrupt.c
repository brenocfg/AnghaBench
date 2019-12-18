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
struct resource {int /*<<< orphan*/  flags; } ;
struct acpi_resource_irq {int interrupt_count; int /*<<< orphan*/  shareable; int /*<<< orphan*/  polarity; int /*<<< orphan*/  triggering; int /*<<< orphan*/ * interrupts; } ;
struct acpi_resource_extended_irq {int interrupt_count; int /*<<< orphan*/  shareable; int /*<<< orphan*/  polarity; int /*<<< orphan*/  triggering; int /*<<< orphan*/ * interrupts; } ;
struct TYPE_2__ {struct acpi_resource_extended_irq extended_irq; struct acpi_resource_irq irq; } ;
struct acpi_resource {int type; TYPE_1__ data; } ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_EXTENDED_IRQ 129 
#define  ACPI_RESOURCE_TYPE_IRQ 128 
 int /*<<< orphan*/  acpi_dev_get_irqresource (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_dev_irqresource_disabled (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gsi (struct acpi_resource_extended_irq*) ; 

bool acpi_dev_resource_interrupt(struct acpi_resource *ares, int index,
				 struct resource *res)
{
	struct acpi_resource_irq *irq;
	struct acpi_resource_extended_irq *ext_irq;

	switch (ares->type) {
	case ACPI_RESOURCE_TYPE_IRQ:
		/*
		 * Per spec, only one interrupt per descriptor is allowed in
		 * _CRS, but some firmware violates this, so parse them all.
		 */
		irq = &ares->data.irq;
		if (index >= irq->interrupt_count) {
			acpi_dev_irqresource_disabled(res, 0);
			return false;
		}
		acpi_dev_get_irqresource(res, irq->interrupts[index],
					 irq->triggering, irq->polarity,
					 irq->shareable, true);
		break;
	case ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		ext_irq = &ares->data.extended_irq;
		if (index >= ext_irq->interrupt_count) {
			acpi_dev_irqresource_disabled(res, 0);
			return false;
		}
		if (is_gsi(ext_irq))
			acpi_dev_get_irqresource(res, ext_irq->interrupts[index],
					 ext_irq->triggering, ext_irq->polarity,
					 ext_irq->shareable, false);
		else
			acpi_dev_irqresource_disabled(res, 0);
		break;
	default:
		res->flags = 0;
		return false;
	}

	return true;
}