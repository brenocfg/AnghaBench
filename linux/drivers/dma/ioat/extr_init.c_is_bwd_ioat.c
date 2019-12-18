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
struct pci_dev {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE0 135 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE1 134 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE2 133 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE3 132 
#define  PCI_DEVICE_ID_INTEL_IOAT_BWD0 131 
#define  PCI_DEVICE_ID_INTEL_IOAT_BWD1 130 
#define  PCI_DEVICE_ID_INTEL_IOAT_BWD2 129 
#define  PCI_DEVICE_ID_INTEL_IOAT_BWD3 128 

bool is_bwd_ioat(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_IOAT_BWD0:
	case PCI_DEVICE_ID_INTEL_IOAT_BWD1:
	case PCI_DEVICE_ID_INTEL_IOAT_BWD2:
	case PCI_DEVICE_ID_INTEL_IOAT_BWD3:
	/* even though not Atom, BDX-DE has same DMA silicon */
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE0:
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE1:
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE2:
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE3:
		return true;
	default:
		return false;
	}
}