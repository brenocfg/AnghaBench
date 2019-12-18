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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_QUIRK_ENABLE_MSI_VM ; 
 scalar_t__ VM_GUEST_NO ; 
 int /*<<< orphan*/ * pci_find_bsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_has_quirk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_honor_msi_blacklist ; 
 int pci_msi_device_blacklisted (int /*<<< orphan*/ *) ; 
 scalar_t__ pcie_chipset ; 
 scalar_t__ pcix_chipset ; 
 scalar_t__ vm_guest ; 

__attribute__((used)) static int
pci_msi_blacklisted(void)
{
	device_t dev;

	if (!pci_honor_msi_blacklist)
		return (0);

	/* Blacklist all non-PCI-express and non-PCI-X chipsets. */
	if (!(pcie_chipset || pcix_chipset)) {
		if (vm_guest != VM_GUEST_NO) {
			/*
			 * Whitelist older chipsets in virtual
			 * machines known to support MSI.
			 */
			dev = pci_find_bsf(0, 0, 0);
			if (dev != NULL)
				return (!pci_has_quirk(pci_get_devid(dev),
					PCI_QUIRK_ENABLE_MSI_VM));
		}
		return (1);
	}

	dev = pci_find_bsf(0, 0, 0);
	if (dev != NULL)
		return (pci_msi_device_blacklisted(dev));
	return (0);
}