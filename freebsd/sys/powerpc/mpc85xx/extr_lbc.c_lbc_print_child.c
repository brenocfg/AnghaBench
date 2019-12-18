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
struct lbc_devinfo {struct resource_list di_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lbc_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
lbc_print_child(device_t dev, device_t child)
{
	struct lbc_devinfo *di;
	struct resource_list *rl;
	int rv;

	di = device_get_ivars(child);
	rl = &di->di_res;

	rv = 0;
	rv += bus_print_child_header(dev, child);
	rv += resource_list_print_type(rl, "mem", SYS_RES_MEMORY, "%#jx");
	rv += resource_list_print_type(rl, "irq", SYS_RES_IRQ, "%jd");
	rv += bus_print_child_footer(dev, child);

	return (rv);
}