#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; } ;
struct pci_dev {struct resource* resource; int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ read; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ bcma_core_pci_hostmode_read_config ; 
 int pci_assign_resource (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_core_pci_fixup_addresses(struct pci_dev *dev)
{
	struct resource *res;
	int pos, err;

	if (dev->bus->ops->read != bcma_core_pci_hostmode_read_config) {
		/* This is not a device on the PCI-core bridge. */
		return;
	}
	if (PCI_SLOT(dev->devfn) == 0)
		return;

	pr_info("PCI: Fixing up addresses %s\n", pci_name(dev));

	for (pos = 0; pos < 6; pos++) {
		res = &dev->resource[pos];
		if (res->flags & (IORESOURCE_IO | IORESOURCE_MEM)) {
			err = pci_assign_resource(dev, pos);
			if (err)
				pr_err("PCI: Problem fixing up the addresses on %s\n",
				       pci_name(dev));
		}
	}
}