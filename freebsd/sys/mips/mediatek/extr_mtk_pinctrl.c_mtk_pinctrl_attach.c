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
 int ENXIO ; 
 int /*<<< orphan*/  SYSCTL_GPIOMODE ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_sysctl_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pinctrl_attach(device_t dev)
{

	if (device_get_unit(dev) != 0) {
		device_printf(dev, "Only one pin control allowed\n");
		return (ENXIO);
	}

	if (bootverbose)
		device_printf(dev, "GPIO mode start: 0x%08x\n",
		    mtk_sysctl_get(SYSCTL_GPIOMODE));

	fdt_pinctrl_register(dev, NULL);
	fdt_pinctrl_configure_tree(dev);

	if (bootverbose)
		device_printf(dev, "GPIO mode end  : 0x%08x\n",
		    mtk_sysctl_get(SYSCTL_GPIOMODE));

	return (0);
}