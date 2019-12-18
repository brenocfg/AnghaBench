#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_3__ {scalar_t__ pci_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iicbus_set_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ *) ; 
 TYPE_1__* slaves ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
chromebook_i2c_identify(driver_t *driver, device_t bus)
{
	device_t controller;
	device_t child;
	int i;

	/*
	 * A stopgap approach to preserve the status quo.
	 * A more intelligent approach is required to correctly
	 * identify a machine model and hardware available on it.
	 * For instance, DMI could be used.
	 * See http://lxr.free-electrons.com/source/drivers/platform/chrome/chromeos_laptop.c
	 */
	controller = device_get_parent(bus);
	if (strcmp(device_get_name(controller), "ig4iic") != 0)
		return;

	for (i = 0; i < nitems(slaves); i++) {
		if (device_find_child(bus, slaves[i].name, -1) != NULL)
			continue;
		if (slaves[i].pci_id != pci_get_devid(controller))
			continue;
		child = BUS_ADD_CHILD(bus, 0, slaves[i].name, -1);
		if (child != NULL)
			iicbus_set_addr(child, slaves[i].addr);
	}
}