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
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
arm_gic_print_child(device_t bus, device_t child)
{
	struct resource_list *rl;
	int rv;

	rv = bus_print_child_header(bus, child);

	rl = BUS_GET_RESOURCE_LIST(bus, child);
	if (rl != NULL) {
		rv += resource_list_print_type(rl, "mem", SYS_RES_MEMORY,
		    "%#jx");
		rv += resource_list_print_type(rl, "irq", SYS_RES_IRQ, "%jd");
	}

	rv += bus_print_child_footer(bus, child);

	return (rv);
}