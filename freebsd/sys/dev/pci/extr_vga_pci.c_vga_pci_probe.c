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
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
#define  PCIC_DISPLAY 129 
#define  PCIC_OLD 128 
 int /*<<< orphan*/  PCIS_OLD_VGA ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_pci_is_boot_display (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vga_pci_probe(device_t dev)
{

	switch (pci_get_class(dev)) {
	case PCIC_DISPLAY:
		break;
	case PCIC_OLD:
		if (pci_get_subclass(dev) != PCIS_OLD_VGA)
			return (ENXIO);
		break;
	default:
		return (ENXIO);
	}

	/* Probe default display. */
	vga_pci_is_boot_display(dev);

	device_set_desc(dev, "VGA-compatible display");
	return (BUS_PROBE_GENERIC);
}