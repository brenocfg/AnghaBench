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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ISA_ORDER_SPECULATIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__* ports_table ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ superio_detect (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
superio_identify(driver_t *driver, device_t parent)
{
	device_t	child;
	int i;

	/*
	 * Don't create child devices if any already exist.
	 * Those could be created via isa hints or if this
	 * driver is loaded, unloaded and then loaded again.
	 */
	if (device_find_child(parent, "superio", -1)) {
		if (bootverbose)
			printf("superio: device(s) already created\n");
		return;
	}

	/*
	 * Create a child for each candidate port.
	 * It would be nice if we could somehow clean up those
	 * that this driver fails to probe.
	 */
	for (i = 0; ports_table[i] != 0; i++) {
		child = BUS_ADD_CHILD(parent, ISA_ORDER_SPECULATIVE,
		    "superio", -1);
		if (child == NULL) {
			device_printf(parent, "failed to add superio child\n");
			continue;
		}
		bus_set_resource(child, SYS_RES_IOPORT,	0, ports_table[i], 2);
		if (superio_detect(child, false, NULL) != 0)
			device_delete_child(parent, child);
	}
}