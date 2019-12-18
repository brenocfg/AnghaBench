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
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,scalar_t__,char**,int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 scalar_t__ devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  device_set_desc (scalar_t__,char*) ; 
 int /*<<< orphan*/  isab_devclass ; 

__attribute__((used)) static int
acpi_isab_probe(device_t dev)
{
	static char *isa_ids[] = { "PNP0A05", "PNP0A06", NULL };
	int rv;
	
	if (acpi_disabled("isab") ||
	    devclass_get_device(isab_devclass, 0) != dev)
		return (ENXIO);
	rv = ACPI_ID_PROBE(device_get_parent(dev), dev, isa_ids, NULL);
	if (rv <= 0)
		device_set_desc(dev, "ACPI Generic ISA bridge");
	return (rv);
}