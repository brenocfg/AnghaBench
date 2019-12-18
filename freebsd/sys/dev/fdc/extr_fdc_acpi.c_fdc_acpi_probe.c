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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVALUATE_OBJECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
fdc_acpi_probe(device_t dev)
{
	device_t bus;
	static char *fdc_ids[] = { "PNP0700", "PNP0701", NULL };
	int rv;

	bus = device_get_parent(dev);
	rv = ACPI_ID_PROBE(bus, dev, fdc_ids, NULL);
	if (rv > 0)
		return (rv);

	if (ACPI_SUCCESS(ACPI_EVALUATE_OBJECT(bus, dev, "_FDE", NULL, NULL)))
		device_set_desc(dev, "floppy drive controller (FDE)");
	else
		device_set_desc(dev, "floppy drive controller");
	return (rv);
}