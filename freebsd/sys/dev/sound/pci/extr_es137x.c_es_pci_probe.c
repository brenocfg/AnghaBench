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
#define  CT4730REV_CT4730_A 142 
#define  CT4730_PCI_ID 141 
#define  CT5880REV_CT5880_C 140 
#define  CT5880REV_CT5880_D 139 
#define  CT5880REV_CT5880_E 138 
#define  CT5880_PCI_ID 137 
 int ENXIO ; 
#define  ES1370_PCI_ID 136 
#define  ES1371REV_CT5880_A 135 
#define  ES1371REV_ES1371_A 134 
#define  ES1371REV_ES1371_B 133 
#define  ES1371REV_ES1373_8 132 
#define  ES1371REV_ES1373_A 131 
#define  ES1371REV_ES1373_B 130 
#define  ES1371_PCI_ID 129 
#define  ES1371_PCI_ID2 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
es_pci_probe(device_t dev)
{
	switch(pci_get_devid(dev)) {
	case ES1370_PCI_ID:
		device_set_desc(dev, "AudioPCI ES1370");
		return (BUS_PROBE_DEFAULT);
	case ES1371_PCI_ID:
		switch(pci_get_revid(dev)) {
		case ES1371REV_ES1371_A:
			device_set_desc(dev, "AudioPCI ES1371-A");
			return (BUS_PROBE_DEFAULT);
		case ES1371REV_ES1371_B:
			device_set_desc(dev, "AudioPCI ES1371-B");
			return (BUS_PROBE_DEFAULT);
		case ES1371REV_ES1373_A:
			device_set_desc(dev, "AudioPCI ES1373-A");
			return (BUS_PROBE_DEFAULT);
		case ES1371REV_ES1373_B:
			device_set_desc(dev, "AudioPCI ES1373-B");
			return (BUS_PROBE_DEFAULT);
		case ES1371REV_ES1373_8:
			device_set_desc(dev, "AudioPCI ES1373-8");
			return (BUS_PROBE_DEFAULT);
		case ES1371REV_CT5880_A:
			device_set_desc(dev, "Creative CT5880-A");
			return (BUS_PROBE_DEFAULT);
		default:
			device_set_desc(dev, "AudioPCI ES1371-?");
			device_printf(dev,
			    "unknown revision %d -- please report to "
			    "freebsd-multimedia@freebsd.org\n",
			    pci_get_revid(dev));
			return (BUS_PROBE_DEFAULT);
		}
	case ES1371_PCI_ID2:
		device_set_desc(dev, "Strange AudioPCI ES1371-? (vid=3274)");
		device_printf(dev,
		    "unknown revision %d -- please report to "
		    "freebsd-multimedia@freebsd.org\n", pci_get_revid(dev));
		return (BUS_PROBE_DEFAULT);
	case CT4730_PCI_ID:
		switch(pci_get_revid(dev)) {
		case CT4730REV_CT4730_A:
			device_set_desc(dev,
			    "Creative SB AudioPCI CT4730/EV1938");
			return (BUS_PROBE_DEFAULT);
		default:
			device_set_desc(dev, "Creative SB AudioPCI CT4730-?");
			device_printf(dev,
			    "unknown revision %d -- please report to "
			    "freebsd-multimedia@freebsd.org\n",
			    pci_get_revid(dev));
			return (BUS_PROBE_DEFAULT);
		}
	case CT5880_PCI_ID:
		switch(pci_get_revid(dev)) {
		case CT5880REV_CT5880_C:
			device_set_desc(dev, "Creative CT5880-C");
			return (BUS_PROBE_DEFAULT);
		case CT5880REV_CT5880_D:
			device_set_desc(dev, "Creative CT5880-D");
			return (BUS_PROBE_DEFAULT);
		case CT5880REV_CT5880_E:
			device_set_desc(dev, "Creative CT5880-E");
			return (BUS_PROBE_DEFAULT);
		default:
			device_set_desc(dev, "Creative CT5880-?");
			device_printf(dev,
			    "unknown revision %d -- please report to "
			    "freebsd-multimedia@freebsd.org\n",
			    pci_get_revid(dev));
			return (BUS_PROBE_DEFAULT);
		}
	default:
		return (ENXIO);
	}
}