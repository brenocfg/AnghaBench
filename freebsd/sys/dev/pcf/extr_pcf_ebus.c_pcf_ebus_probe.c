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
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char const* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
pcf_ebus_probe(device_t dev)
{
	const char *compat;

	/*
	 * We must not attach to this i2c device if this is a system with
	 * a boot-bus controller. Additionally testing the compatibility
	 * property will hopefully take care of this.
	 */
	if (strcmp("i2c", ofw_bus_get_name(dev)) == 0) {
		compat = ofw_bus_get_compat(dev);
		if (compat != NULL && strcmp("i2cpcf,8584", compat) == 0) {
			device_set_desc(dev, "PCF8584 I2C bus controller");
			return (0);
		}
	}
	return (ENXIO);
}