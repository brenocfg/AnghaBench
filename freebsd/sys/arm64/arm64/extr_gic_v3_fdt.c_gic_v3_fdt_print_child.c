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
struct gic_v3_ofw_devinfo {struct resource_list di_rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gic_v3_ofw_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gic_v3_fdt_print_child(device_t bus, device_t child)
{
	struct gic_v3_ofw_devinfo *di = device_get_ivars(child);
	struct resource_list *rl = &di->di_rl;
	int retval = 0;

	retval += bus_print_child_header(bus, child);
	retval += resource_list_print_type(rl, "mem", SYS_RES_MEMORY, "%#jx");
	retval += bus_print_child_footer(bus, child);

	return (retval);
}