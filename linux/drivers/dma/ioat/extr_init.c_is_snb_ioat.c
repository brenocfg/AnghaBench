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
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB0 137 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB1 136 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB2 135 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB3 134 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB4 133 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB5 132 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB6 131 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB7 130 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB8 129 
#define  PCI_DEVICE_ID_INTEL_IOAT_SNB9 128 

__attribute__((used)) static bool is_snb_ioat(struct pci_dev *pdev)
{
	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_IOAT_SNB0:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB1:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB2:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB3:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB4:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB5:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB6:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB7:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB8:
	case PCI_DEVICE_ID_INTEL_IOAT_SNB9:
		return true;
	default:
		return false;
	}
}