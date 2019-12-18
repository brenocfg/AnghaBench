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
struct macio_devinfo {struct resource_list mdi_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct macio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
macio_probe_nomatch(device_t dev, device_t child)
{
        struct macio_devinfo *dinfo;
        struct resource_list *rl;
	const char *type;

	if (bootverbose) {
		dinfo = device_get_ivars(child);
		rl = &dinfo->mdi_resources;

		if ((type = ofw_bus_get_type(child)) == NULL)
			type = "(unknown)";
		device_printf(dev, "<%s, %s>", type, ofw_bus_get_name(child));
		resource_list_print_type(rl, "mem", SYS_RES_MEMORY, "%#jx");
		resource_list_print_type(rl, "irq", SYS_RES_IRQ, "%jd");
		printf(" (no driver attached)\n");
	}
}