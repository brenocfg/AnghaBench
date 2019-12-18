#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bus_type {TYPE_1__* p; int /*<<< orphan*/  bus_groups; scalar_t__ dev_root; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsys; int /*<<< orphan*/ * devices_kset; int /*<<< orphan*/ * drivers_kset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_attr_uevent ; 
 int /*<<< orphan*/  bus_remove_file (struct bus_type*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_remove_groups (struct bus_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_probe_files (struct bus_type*) ; 

void bus_unregister(struct bus_type *bus)
{
	pr_debug("bus: '%s': unregistering\n", bus->name);
	if (bus->dev_root)
		device_unregister(bus->dev_root);
	bus_remove_groups(bus, bus->bus_groups);
	remove_probe_files(bus);
	kset_unregister(bus->p->drivers_kset);
	kset_unregister(bus->p->devices_kset);
	bus_remove_file(bus, &bus_attr_uevent);
	kset_unregister(&bus->p->subsys);
}