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
struct pci_dev {int pme_support; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCI_PM_CAP_PME_D3 ; 
 int PCI_PM_CAP_PME_D3cold ; 
 int PCI_PM_CAP_PME_SHIFT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void pci_fixup_amd_ehci_pme(struct pci_dev *dev)
{
	dev_info(&dev->dev, "PME# does not work under D3, disabling it\n");
	dev->pme_support &= ~((PCI_PM_CAP_PME_D3 | PCI_PM_CAP_PME_D3cold)
		>> PCI_PM_CAP_PME_SHIFT);
}