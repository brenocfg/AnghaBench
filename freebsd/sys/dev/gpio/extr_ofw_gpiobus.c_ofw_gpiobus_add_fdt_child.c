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
struct gpiobus_ivar {int npins; int /*<<< orphan*/ * pins; } ;
struct ofw_gpiobus_devinfo {struct gpiobus_ivar opd_dinfo; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_PIN_SETNAME (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ofw_bus_find_child_device_by_phandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_gpiobus_destroy_devinfo (int /*<<< orphan*/ *,struct ofw_gpiobus_devinfo*) ; 
 struct ofw_gpiobus_devinfo* ofw_gpiobus_setup_devinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

device_t
ofw_gpiobus_add_fdt_child(device_t bus, const char *drvname, phandle_t child)
{
	device_t childdev;
	int i;
	struct gpiobus_ivar *devi;
	struct ofw_gpiobus_devinfo *dinfo;

	/*
	 * Check to see if we already have a child for @p child, and if so
	 * return it.
	 */
	childdev = ofw_bus_find_child_device_by_phandle(bus, child);
	if (childdev != NULL)
		return (childdev);

	/*
	 * Set up the GPIO child and OFW bus layer devinfo and add it to bus.
	 */
	childdev = device_add_child(bus, drvname, -1);
	if (childdev == NULL)
		return (NULL);
	dinfo = ofw_gpiobus_setup_devinfo(bus, childdev, child);
	if (dinfo == NULL) {
		device_delete_child(bus, childdev);
		return (NULL);
	}
	if (device_probe_and_attach(childdev) != 0) {
		ofw_gpiobus_destroy_devinfo(bus, dinfo);
		device_delete_child(bus, childdev);
		return (NULL);
	}
	/* Use the child name as pin name. */
	devi = &dinfo->opd_dinfo;
	for (i = 0; i < devi->npins; i++)
		GPIOBUS_PIN_SETNAME(bus, devi->pins[i],
		    device_get_nameunit(childdev));

	return (childdev);
}