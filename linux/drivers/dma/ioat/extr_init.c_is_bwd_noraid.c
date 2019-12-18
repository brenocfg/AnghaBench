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
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE0 133 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE1 132 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE2 131 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDXDE3 130 
#define  PCI_DEVICE_ID_INTEL_IOAT_BWD2 129 
#define  PCI_DEVICE_ID_INTEL_IOAT_BWD3 128 

__attribute__((used)) static bool is_bwd_noraid(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_IOAT_BWD2:
	case PCI_DEVICE_ID_INTEL_IOAT_BWD3:
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE0:
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE1:
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE2:
	case PCI_DEVICE_ID_INTEL_IOAT_BDXDE3:
		return true;
	default:
		return false;
	}

}