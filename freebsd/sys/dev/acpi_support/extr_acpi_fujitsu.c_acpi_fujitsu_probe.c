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
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fujitsu_ids ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int
acpi_fujitsu_probe(device_t dev)
{
	char *name;
	char buffer[64];
	int rv;

	rv =  ACPI_ID_PROBE(device_get_parent(dev), dev, fujitsu_ids, &name);
	if (acpi_disabled("fujitsu") || rv > 0 || device_get_unit(dev) > 1)
		return (ENXIO);
	sprintf(buffer, "Fujitsu Function Hotkeys %s", name);
	device_set_desc_copy(dev, buffer);

	return (rv);
}