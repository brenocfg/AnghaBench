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
 int /*<<< orphan*/  PCI_QUIRK_DISABLE_MSIX ; 
 int /*<<< orphan*/ * pci_find_bsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_has_quirk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_honor_msi_blacklist ; 
 int pci_msi_blacklisted () ; 

__attribute__((used)) static int
pci_msix_blacklisted(void)
{
	device_t dev;

	if (!pci_honor_msi_blacklist)
		return (0);

	dev = pci_find_bsf(0, 0, 0);
	if (dev != NULL && pci_has_quirk(pci_get_devid(dev),
	    PCI_QUIRK_DISABLE_MSIX))
		return (1);

	return (pci_msi_blacklisted());
}