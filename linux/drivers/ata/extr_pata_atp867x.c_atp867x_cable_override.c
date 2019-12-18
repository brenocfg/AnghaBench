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
struct pci_dev {scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_ARTOP_ATP867A ; 
 scalar_t__ PCI_DEVICE_ID_ARTOP_ATP867B ; 
 scalar_t__ PCI_VENDOR_ID_ARTOP ; 

__attribute__((used)) static int atp867x_cable_override(struct pci_dev *pdev)
{
	if (pdev->subsystem_vendor == PCI_VENDOR_ID_ARTOP &&
		(pdev->subsystem_device == PCI_DEVICE_ID_ARTOP_ATP867A ||
		 pdev->subsystem_device == PCI_DEVICE_ID_ARTOP_ATP867B)) {
		return 1;
	}
	return 0;
}