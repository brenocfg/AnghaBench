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
#define  PCI_DEVICE_3DFX_VOODOO1 130 
#define  PCI_DEVICE_3DFX_VOODOO2 129 
#define  PCI_DEVICE_ALLIANCE_AT3D 128 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tdfx_probe(device_t dev)
{
	/*
	 * probe routine called on kernel boot to register supported devices. We get
	 * a device structure to work with, and we can test the VENDOR/DEVICE IDs to
	 * see if this PCI device is one that we support. Return BUS_PRROBE_DEFAULT
	 * if yes, ENXIO if not.
	 */
	switch(pci_get_devid(dev)) {
	case PCI_DEVICE_ALLIANCE_AT3D:
		device_set_desc(dev, "ProMotion At3D 3D Accelerator");
		return BUS_PROBE_DEFAULT;
	case PCI_DEVICE_3DFX_VOODOO2:
		device_set_desc(dev, "3DFX Voodoo II 3D Accelerator");
		return BUS_PROBE_DEFAULT;
	/*case PCI_DEVICE_3DFX_BANSHEE:
		device_set_desc(dev, "3DFX Voodoo Banshee 2D/3D Graphics Accelerator");
		return BUS_PROBE_DEFAULT;
	case PCI_DEVICE_3DFX_VOODOO3:
		device_set_desc(dev, "3DFX Voodoo3 2D/3D Graphics Accelerator");
		return BUS_PROBE_DEFAULT;*/
	case PCI_DEVICE_3DFX_VOODOO1:
		device_set_desc(dev, "3DFX Voodoo Graphics 3D Accelerator");
		return BUS_PROBE_DEFAULT;
	}

	return ENXIO;
}