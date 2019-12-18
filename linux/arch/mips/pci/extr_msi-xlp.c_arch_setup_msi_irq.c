#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ is_msix; } ;
struct msi_desc {TYPE_1__ msi_attrib; } ;

/* Variables and functions */
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nlm_get_pcie_base (int,int) ; 
 struct pci_dev* xlp_get_pcie_link (struct pci_dev*) ; 
 int xlp_setup_msi (int /*<<< orphan*/ ,int,int,struct msi_desc*) ; 
 int xlp_setup_msix (int /*<<< orphan*/ ,int,int,struct msi_desc*) ; 

int arch_setup_msi_irq(struct pci_dev *dev, struct msi_desc *desc)
{
	struct pci_dev *lnkdev;
	uint64_t lnkbase;
	int node, link, slot;

	lnkdev = xlp_get_pcie_link(dev);
	if (lnkdev == NULL) {
		dev_err(&dev->dev, "Could not find bridge\n");
		return 1;
	}
	slot = PCI_SLOT(lnkdev->devfn);
	link = PCI_FUNC(lnkdev->devfn);
	node = slot / 8;
	lnkbase = nlm_get_pcie_base(node, link);

	if (desc->msi_attrib.is_msix)
		return xlp_setup_msix(lnkbase, node, link, desc);
	else
		return xlp_setup_msi(lnkbase, node, link, desc);
}