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
struct pci_devinfo {struct resource_list resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_print_child_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int,...) ; 
 scalar_t__ resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

int
pci_print_child(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo;
	struct resource_list *rl;
	int retval = 0;

	dinfo = device_get_ivars(child);
	rl = &dinfo->resources;

	retval += bus_print_child_header(dev, child);

	retval += resource_list_print_type(rl, "port", SYS_RES_IOPORT, "%#jx");
	retval += resource_list_print_type(rl, "mem", SYS_RES_MEMORY, "%#jx");
	retval += resource_list_print_type(rl, "irq", SYS_RES_IRQ, "%jd");
	if (device_get_flags(dev))
		retval += printf(" flags %#x", device_get_flags(dev));

	retval += printf(" at device %d.%d", pci_get_slot(child),
	    pci_get_function(child));

	retval += bus_print_child_domain(dev, child);
	retval += bus_print_child_footer(dev, child);

	return (retval);
}