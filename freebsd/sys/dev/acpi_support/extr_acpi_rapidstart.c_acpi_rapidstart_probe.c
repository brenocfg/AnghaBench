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
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rapidstart_ids ; 

__attribute__((used)) static int
acpi_rapidstart_probe(device_t dev)
{
	int rv;

	if (acpi_disabled("rapidstart") ||
	    device_get_unit(dev) != 0)
		return (ENXIO);
	rv = ACPI_ID_PROBE(device_get_parent(dev), dev, rapidstart_ids, NULL);
	if (rv <= 0)
		device_set_desc(dev, "Intel Rapid Start ACPI device");

	return (rv);
	
}