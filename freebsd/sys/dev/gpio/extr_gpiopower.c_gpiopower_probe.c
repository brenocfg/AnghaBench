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
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gpiopower_probe(device_t dev)
{

	if (ofw_bus_is_compatible(dev, "gpio-poweroff")) {
		device_set_desc(dev, "GPIO poweroff control");
		return (0);
	} else if (ofw_bus_is_compatible(dev, "gpio-restart")) {
		device_set_desc(dev, "GPIO restart control");
		return (0);
	}

	return (ENXIO);
}