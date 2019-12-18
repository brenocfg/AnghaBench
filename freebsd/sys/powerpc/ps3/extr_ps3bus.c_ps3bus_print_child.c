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
struct ps3bus_devinfo {int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ps3bus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ps3bus_print_child(device_t dev, device_t child)
{
	struct ps3bus_devinfo *dinfo = device_get_ivars(child);
	int retval = 0;

	retval += bus_print_child_header(dev, child);
	retval += resource_list_print_type(&dinfo->resources, "mem",
	    SYS_RES_MEMORY, "%#jx");
	retval += resource_list_print_type(&dinfo->resources, "irq",
	    SYS_RES_IRQ, "%jd");

	retval += bus_print_child_footer(dev, child);

	return (retval);
}