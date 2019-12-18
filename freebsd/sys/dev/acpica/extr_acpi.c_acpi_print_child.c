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
struct acpi_device {struct resource_list ad_rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bus_print_child_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 struct acpi_device* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int) ; 
 scalar_t__ resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
acpi_print_child(device_t bus, device_t child)
{
    struct acpi_device	 *adev = device_get_ivars(child);
    struct resource_list *rl = &adev->ad_rl;
    int retval = 0;

    retval += bus_print_child_header(bus, child);
    retval += resource_list_print_type(rl, "port",  SYS_RES_IOPORT, "%#jx");
    retval += resource_list_print_type(rl, "iomem", SYS_RES_MEMORY, "%#jx");
    retval += resource_list_print_type(rl, "irq",   SYS_RES_IRQ,    "%jd");
    retval += resource_list_print_type(rl, "drq",   SYS_RES_DRQ,    "%jd");
    if (device_get_flags(child))
	retval += printf(" flags %#x", device_get_flags(child));
    retval += bus_print_child_domain(bus, child);
    retval += bus_print_child_footer(bus, child);

    return (retval);
}