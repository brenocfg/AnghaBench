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
struct iicbus_ivar {int addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 struct iicbus_ivar* IICBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ resource_int_value (char const*,int,char*,int*) ; 

__attribute__((used)) static void
iicbus_hinted_child(device_t bus, const char *dname, int dunit)
{
	device_t child;
	int irq;
	struct iicbus_ivar *devi;

	child = BUS_ADD_CHILD(bus, 0, dname, dunit);
	devi = IICBUS_IVAR(child);
	resource_int_value(dname, dunit, "addr", &devi->addr);
	if (resource_int_value(dname, dunit, "irq", &irq) == 0) {
		if (bus_set_resource(child, SYS_RES_IRQ, 0, irq, 1) != 0)
			device_printf(bus,
			    "warning: bus_set_resource() failed\n");
	}
}