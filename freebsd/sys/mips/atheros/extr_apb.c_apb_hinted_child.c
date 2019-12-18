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
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 scalar_t__ resource_int_value (char const*,int,char*,int*) ; 
 scalar_t__ resource_long_value (char const*,int,char*,long*) ; 

__attribute__((used)) static void
apb_hinted_child(device_t bus, const char *dname, int dunit)
{
	device_t		child;
	long			maddr;
	int			msize;
	int			irq;
	int			result;
	int			mem_hints_count;

	child = BUS_ADD_CHILD(bus, 0, dname, dunit);

	/*
	 * Set hard-wired resources for hinted child using
	 * specific RIDs.
	 */
	mem_hints_count = 0;
	if (resource_long_value(dname, dunit, "maddr", &maddr) == 0)
		mem_hints_count++;
	if (resource_int_value(dname, dunit, "msize", &msize) == 0)
		mem_hints_count++;

	/* check if all info for mem resource has been provided */
	if ((mem_hints_count > 0) && (mem_hints_count < 2)) {
		printf("Either maddr or msize hint is missing for %s%d\n",
		    dname, dunit);
	} else if (mem_hints_count) {
		result = bus_set_resource(child, SYS_RES_MEMORY, 0,
		    maddr, msize);
		if (result != 0)
			device_printf(bus, 
			    "warning: bus_set_resource() failed\n");
	}

	if (resource_int_value(dname, dunit, "irq", &irq) == 0) {
		result = bus_set_resource(child, SYS_RES_IRQ, 0, irq, 1);
		if (result != 0)
			device_printf(bus,
			    "warning: bus_set_resource() failed\n");
	}
}