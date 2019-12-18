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
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX0 137 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX1 136 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX2 135 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX3 134 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX4 133 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX5 132 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX6 131 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX7 130 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX8 129 
#define  PCI_DEVICE_ID_INTEL_IOAT_BDX9 128 

__attribute__((used)) static bool is_bdx_ioat(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_IOAT_BDX0:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX1:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX2:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX3:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX4:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX5:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX6:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX7:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX8:
	case PCI_DEVICE_ID_INTEL_IOAT_BDX9:
		return true;
	default:
		return false;
	}
}