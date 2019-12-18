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
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_gpiobus_unregister_provider (int /*<<< orphan*/ ) ; 

int
gpiobus_detach_bus(device_t dev)
{
	int err;

#ifdef FDT
	ofw_gpiobus_unregister_provider(dev);
#endif
	err = bus_generic_detach(dev);
	if (err != 0)
		return (err);

	return (device_delete_children(dev));
}