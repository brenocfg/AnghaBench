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
 int ENXIO ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_throttle_probe(device_t dev)
{

	if (resource_disabled("acpi_throttle", 0))
		return (ENXIO);

	/*
	 * On i386 platforms at least, ACPI throttling is accomplished by
	 * the chipset modulating the STPCLK# pin based on the duty cycle.
	 * Since p4tcc uses the same mechanism (but internal to the CPU),
	 * we disable acpi_throttle when p4tcc is also present.
	 */
	if (device_find_child(device_get_parent(dev), "p4tcc", -1) &&
	    !resource_disabled("p4tcc", 0))
		return (ENXIO);

	device_set_desc(dev, "ACPI CPU Throttling");
	return (0);
}