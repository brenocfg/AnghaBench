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
#define  VIA8233_PCI_ID 135 
#define  VIA8233_REV_ID_8233 134 
#define  VIA8233_REV_ID_8233A 133 
#define  VIA8233_REV_ID_8233C 132 
#define  VIA8233_REV_ID_8233PRE 131 
#define  VIA8233_REV_ID_8235 130 
#define  VIA8233_REV_ID_8237 129 
#define  VIA8233_REV_ID_8251 128 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
via_probe(device_t dev)
{
	switch(pci_get_devid(dev)) {
	case VIA8233_PCI_ID:
		switch(pci_get_revid(dev)) {
		case VIA8233_REV_ID_8233PRE:
			device_set_desc(dev, "VIA VT8233 (pre)");
			return (BUS_PROBE_DEFAULT);
		case VIA8233_REV_ID_8233C:
			device_set_desc(dev, "VIA VT8233C");
			return (BUS_PROBE_DEFAULT);
		case VIA8233_REV_ID_8233:
			device_set_desc(dev, "VIA VT8233");
			return (BUS_PROBE_DEFAULT);
		case VIA8233_REV_ID_8233A:
			device_set_desc(dev, "VIA VT8233A");
			return (BUS_PROBE_DEFAULT);
		case VIA8233_REV_ID_8235:
			device_set_desc(dev, "VIA VT8235");
			return (BUS_PROBE_DEFAULT);
		case VIA8233_REV_ID_8237:
			device_set_desc(dev, "VIA VT8237");
			return (BUS_PROBE_DEFAULT);
		case VIA8233_REV_ID_8251:
			device_set_desc(dev, "VIA VT8251");
			return (BUS_PROBE_DEFAULT);
		default:
			device_set_desc(dev, "VIA VT8233X");	/* Unknown */
			return (BUS_PROBE_DEFAULT);
		}
	}
	return (ENXIO);
}