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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_devices_only ; 
 int /*<<< orphan*/  ofw_pcibus_enum_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_pcibus_enum_devtree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_attach_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_get_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_pcibus_attach(device_t dev)
{
	u_int busno, domain;
	int error;

	error = pci_attach_common(dev);
	if (error)
		return (error);
	domain = pcib_get_domain(dev);
	busno = pcib_get_bus(dev);

	/*
	 * Attach those children represented in the device tree.
	 */

	ofw_pcibus_enum_devtree(dev, domain, busno);

	/*
	 * We now attach any laggard devices. FDT, for instance, allows
	 * the device tree to enumerate only some PCI devices. Apple's
	 * OF device tree on some Grackle-based hardware can also miss
	 * functions on multi-function cards.
	 */

	if (!ofw_devices_only)
		ofw_pcibus_enum_bus(dev, domain, busno);

	return (bus_generic_attach(dev));
}