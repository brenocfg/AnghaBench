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
 scalar_t__ GPIO_BASE ; 
 scalar_t__ GPIO_EXTINT_BASE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct macgpio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
macgpio_print_child(device_t dev, device_t child)
{
        struct macgpio_devinfo *dinfo;
        int retval = 0;

        dinfo = device_get_ivars(child);

        retval += bus_print_child_header(dev, child);
	
	if (dinfo->gpio_num >= GPIO_BASE)
		printf(" gpio %d", dinfo->gpio_num - GPIO_BASE);
	else if (dinfo->gpio_num >= GPIO_EXTINT_BASE)
		printf(" extint-gpio %d", dinfo->gpio_num - GPIO_EXTINT_BASE);
	else if (dinfo->gpio_num >= 0)
		printf(" addr 0x%02x", dinfo->gpio_num); /* should not happen */

	resource_list_print_type(&dinfo->mdi_resources, "irq", SYS_RES_IRQ, 
	    "%jd");
        retval += bus_print_child_footer(dev, child);

        return (retval);
}