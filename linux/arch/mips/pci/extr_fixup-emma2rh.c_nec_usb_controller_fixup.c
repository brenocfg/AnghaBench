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
struct pci_dev {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 scalar_t__ EMMA2RH_USB_SLOT ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static void nec_usb_controller_fixup(struct pci_dev *dev)
{
	if (PCI_SLOT(dev->devfn) == EMMA2RH_USB_SLOT)
		/* on board USB controller configuration */
		pci_write_config_dword(dev, 0xe4, 1 << 5);
}