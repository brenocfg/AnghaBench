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
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_HOST ; 
 scalar_t__ agp_find_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_apple_probe(device_t dev)
{

	if (resource_disabled("agp", device_get_unit(dev)))
		return (ENXIO);

	if (pci_get_class(dev) != PCIC_BRIDGE
	    || pci_get_subclass(dev) != PCIS_BRIDGE_HOST)
		return (ENXIO);

	if (agp_find_caps(dev) == 0)
		return (ENXIO);

	if (pci_get_class(dev) != PCIC_BRIDGE
	    || pci_get_subclass(dev) != PCIS_BRIDGE_HOST)
		return (ENXIO);

	switch (pci_get_devid(dev)) {
	case 0x0020106b:
	case 0x0027106b:
		device_set_desc(dev, "Apple UniNorth AGP Bridge");
		return (BUS_PROBE_DEFAULT);
	case 0x002d106b:
		device_set_desc(dev, "Apple UniNorth 1.5 AGP Bridge");
		return (BUS_PROBE_DEFAULT);
	case 0x0034106b:
		device_set_desc(dev, "Apple UniNorth 2 AGP Bridge");
		return (BUS_PROBE_DEFAULT);
	case 0x004b106b:
	case 0x0058106b:
	case 0x0059106b:
		device_set_desc(dev, "Apple U3 AGP Bridge");
		return (BUS_PROBE_DEFAULT);
	case 0x0066106b:
		device_set_desc(dev, "Apple Intrepid AGP Bridge");
		return (BUS_PROBE_DEFAULT);
	}

	return (ENXIO);
}