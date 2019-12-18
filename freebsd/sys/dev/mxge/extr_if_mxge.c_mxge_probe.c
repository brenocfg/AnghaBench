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
 scalar_t__ MXGE_PCI_DEVICE_Z8E ; 
 scalar_t__ MXGE_PCI_DEVICE_Z8E_9 ; 
#define  MXGE_PCI_REV_Z8E 129 
#define  MXGE_PCI_REV_Z8ES 128 
 scalar_t__ MXGE_PCI_VENDOR_MYRICOM ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mxge_probe(device_t dev)
{
	int rev;


	if ((pci_get_vendor(dev) == MXGE_PCI_VENDOR_MYRICOM) &&
	    ((pci_get_device(dev) == MXGE_PCI_DEVICE_Z8E) ||
	     (pci_get_device(dev) == MXGE_PCI_DEVICE_Z8E_9))) {
		rev = pci_get_revid(dev);
		switch (rev) {
		case MXGE_PCI_REV_Z8E:
			device_set_desc(dev, "Myri10G-PCIE-8A");
			break;
		case MXGE_PCI_REV_Z8ES:
			device_set_desc(dev, "Myri10G-PCIE-8B");
			break;
		default:
			device_set_desc(dev, "Myri10G-PCIE-8??");
			device_printf(dev, "Unrecognized rev %d NIC\n",
				      rev);
			break;	
		}
		return 0;
	}
	return ENXIO;
}