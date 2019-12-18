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
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 int /*<<< orphan*/  bootverbose ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
coretemp_probe(device_t dev)
{
	if (resource_disabled("coretemp", 0))
		return (ENXIO);

	device_set_desc(dev, "CPU On-Die Thermal Sensors");

	if (!bootverbose && device_get_unit(dev) != 0)
		device_quiet(dev);

	return (BUS_PROBE_GENERIC);
}