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
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vga_pci_is_boot_display (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vga_pci_attach(device_t dev)
{

	bus_generic_probe(dev);

	/* Always create a drm child for now to make it easier on drm. */
	device_add_child(dev, "drm", -1);
	device_add_child(dev, "drmn", -1);
	bus_generic_attach(dev);

	if (vga_pci_is_boot_display(dev))
		device_printf(dev, "Boot video device\n");

	return (0);
}