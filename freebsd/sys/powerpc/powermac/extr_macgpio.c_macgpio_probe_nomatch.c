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
struct macgpio_devinfo {scalar_t__ gpio_num; int /*<<< orphan*/  mdi_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bootverbose ; 
 struct macgpio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
macgpio_probe_nomatch(device_t dev, device_t child)
{
        struct macgpio_devinfo *dinfo;
	const char *type;

	if (bootverbose) {
		dinfo = device_get_ivars(child);

		if ((type = ofw_bus_get_type(child)) == NULL)
			type = "(unknown)";
		device_printf(dev, "<%s, %s>", type, ofw_bus_get_name(child));
		if (dinfo->gpio_num >= 0)
			printf(" gpio %d",dinfo->gpio_num);
		resource_list_print_type(&dinfo->mdi_resources, "irq", 
		    SYS_RES_IRQ, "%jd");
		printf(" (no driver attached)\n");
	}
}