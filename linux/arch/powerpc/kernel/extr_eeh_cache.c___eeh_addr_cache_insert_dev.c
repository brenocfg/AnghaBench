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
struct pci_dn {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct eeh_dev {int /*<<< orphan*/  pe; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 int PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eeh_addr_cache_insert (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct pci_dn* pci_get_pdn_by_devfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int) ; 
 unsigned long pci_resource_flags (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 struct eeh_dev* pdn_to_eeh_dev (struct pci_dn*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __eeh_addr_cache_insert_dev(struct pci_dev *dev)
{
	struct pci_dn *pdn;
	struct eeh_dev *edev;
	int i;

	pdn = pci_get_pdn_by_devfn(dev->bus, dev->devfn);
	if (!pdn) {
		pr_warn("PCI: no pci dn found for dev=%s\n",
			pci_name(dev));
		return;
	}

	edev = pdn_to_eeh_dev(pdn);
	if (!edev) {
		pr_warn("PCI: no EEH dev found for %s\n",
			pci_name(dev));
		return;
	}

	/* Skip any devices for which EEH is not enabled. */
	if (!edev->pe) {
		dev_dbg(&dev->dev, "EEH: Skip building address cache\n");
		return;
	}

	/*
	 * Walk resources on this device, poke the first 7 (6 normal BAR and 1
	 * ROM BAR) into the tree.
	 */
	for (i = 0; i <= PCI_ROM_RESOURCE; i++) {
		resource_size_t start = pci_resource_start(dev,i);
		resource_size_t end = pci_resource_end(dev,i);
		unsigned long flags = pci_resource_flags(dev,i);

		/* We are interested only bus addresses, not dma or other stuff */
		if (0 == (flags & (IORESOURCE_IO | IORESOURCE_MEM)))
			continue;
		if (start == 0 || ~start == 0 || end == 0 || ~end == 0)
			 continue;
		eeh_addr_cache_insert(dev, start, end, flags);
	}
}