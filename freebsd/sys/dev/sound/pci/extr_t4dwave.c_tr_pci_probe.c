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
#define  ALI_PCI_ID 131 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
#define  SPA_PCI_ID 130 
#define  TDX_PCI_ID 129 
#define  TNX_PCI_ID 128 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tr_pci_probe(device_t dev)
{
	switch (pci_get_devid(dev)) {
		case SPA_PCI_ID:
			device_set_desc(dev, "SiS 7018");
			return BUS_PROBE_DEFAULT;
		case ALI_PCI_ID:
			device_set_desc(dev, "Acer Labs M5451");
			return BUS_PROBE_DEFAULT;
		case TDX_PCI_ID:
			device_set_desc(dev, "Trident 4DWave DX");
			return BUS_PROBE_DEFAULT;
		case TNX_PCI_ID:
			device_set_desc(dev, "Trident 4DWave NX");
			return BUS_PROBE_DEFAULT;
	}

	return ENXIO;
}