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
typedef  scalar_t__ device_t ;

/* Variables and functions */
 scalar_t__ BUS_ADD_CHILD (scalar_t__,int,char const*,int) ; 
 int ISACFGATTR_HINTS ; 
 int ISA_ORDER_SENSITIVE ; 
 int ISA_ORDER_SPECULATIVE ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_set_resource (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_disable (scalar_t__) ; 
 int isa_get_configattr (scalar_t__) ; 
 int /*<<< orphan*/  isa_set_configattr (scalar_t__,int) ; 
 scalar_t__ resource_disabled (char const*,int) ; 
 scalar_t__ resource_int_value (char const*,int,char*,int*) ; 

void
isa_hinted_child(device_t parent, const char *name, int unit)
{
	device_t	child;
	int		sensitive, start, count;
	int		order;

	/* device-specific flag overrides any wildcard */
	sensitive = 0;
	if (resource_int_value(name, unit, "sensitive", &sensitive) != 0)
		resource_int_value(name, -1, "sensitive", &sensitive);

	if (sensitive)
		order = ISA_ORDER_SENSITIVE;
	else
		order = ISA_ORDER_SPECULATIVE;

	child = BUS_ADD_CHILD(parent, order, name, unit);
	if (child == 0)
		return;

	start = 0;
	count = 0;
	resource_int_value(name, unit, "port", &start);
	resource_int_value(name, unit, "portsize", &count);
	if (start > 0 || count > 0)
		bus_set_resource(child, SYS_RES_IOPORT, 0, start, count);

	start = 0;
	count = 0;
	resource_int_value(name, unit, "maddr", &start);
	resource_int_value(name, unit, "msize", &count);
	if (start > 0 || count > 0)
		bus_set_resource(child, SYS_RES_MEMORY, 0, start, count);

	if (resource_int_value(name, unit, "irq", &start) == 0 && start > 0)
		bus_set_resource(child, SYS_RES_IRQ, 0, start, 1);

	if (resource_int_value(name, unit, "drq", &start) == 0 && start >= 0)
		bus_set_resource(child, SYS_RES_DRQ, 0, start, 1);

	if (resource_disabled(name, unit))
		device_disable(child);

	isa_set_configattr(child, (isa_get_configattr(child)|ISACFGATTR_HINTS));
}