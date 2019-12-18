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
 int /*<<< orphan*/  BUS_HINTED_CHILD (int /*<<< orphan*/ ,char const*,int) ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_find_match (int*,char const**,int*,char*,char const*) ; 

void
bus_enumerate_hinted_children(device_t bus)
{
	int i;
	const char *dname, *busname;
	int dunit;

	/*
	 * enumerate all devices on the specific bus
	 */
	busname = device_get_nameunit(bus);
	i = 0;
	while (resource_find_match(&i, &dname, &dunit, "at", busname) == 0)
		BUS_HINTED_CHILD(bus, dname, dunit);

	/*
	 * and all the generic ones.
	 */
	busname = device_get_name(bus);
	i = 0;
	while (resource_find_match(&i, &dname, &dunit, "at", busname) == 0)
		BUS_HINTED_CHILD(bus, dname, dunit);
}