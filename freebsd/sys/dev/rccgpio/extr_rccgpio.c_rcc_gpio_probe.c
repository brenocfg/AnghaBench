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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int RCC_GPIO_BASE ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int isa_get_port (int /*<<< orphan*/ ) ; 
 char* kern_getenv (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
rcc_gpio_probe(device_t dev)
{
	char *prod;
	int port;

	/*
	 * We don't know of any PnP ID's for this GPIO controller.
	 */
	if (isa_get_logicalid(dev) != 0)
		return (ENXIO);

	/*
	 * We have to have an IO port hint that is valid.
	 */
	port = isa_get_port(dev);
	if (port != RCC_GPIO_BASE)
		return (ENXIO);

	prod = kern_getenv("smbios.system.product");
	if (prod == NULL ||
	    (strcmp(prod, "RCC-VE") != 0 && strcmp(prod, "RCC-DFF") != 0))
		return (ENXIO);

	device_set_desc(dev, "RCC-VE/DFF GPIO controller");

	return (BUS_PROBE_DEFAULT);
}