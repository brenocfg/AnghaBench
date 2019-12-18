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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_gpiobus_register_provider (int /*<<< orphan*/ *) ; 

device_t
gpiobus_attach_bus(device_t dev)
{
	device_t busdev;

	busdev = device_add_child(dev, "gpiobus", -1);
	if (busdev == NULL)
		return (NULL);
	if (device_add_child(dev, "gpioc", -1) == NULL) {
		device_delete_child(dev, busdev);
		return (NULL);
	}
#ifdef FDT
	ofw_gpiobus_register_provider(dev);
#endif
	bus_generic_attach(dev);

	return (busdev);
}