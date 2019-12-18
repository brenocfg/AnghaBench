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
struct resource {int /*<<< orphan*/  flags; scalar_t__ parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dma_ops; int /*<<< orphan*/  groups; } ;
struct pci_dev {int no_vf_scan; struct resource* resource; TYPE_1__ dev; scalar_t__ is_physfn; } ;

/* Variables and functions */
 int PCI_BAR_COUNT ; 
 int /*<<< orphan*/  pci_claim_resource (struct pci_dev*,int) ; 
 int /*<<< orphan*/  s390_pci_dma_ops ; 
 int /*<<< orphan*/  zpci_attr_groups ; 
 int /*<<< orphan*/  zpci_map_resources (struct pci_dev*) ; 

int pcibios_add_device(struct pci_dev *pdev)
{
	struct resource *res;
	int i;

	if (pdev->is_physfn)
		pdev->no_vf_scan = 1;

	pdev->dev.groups = zpci_attr_groups;
	pdev->dev.dma_ops = &s390_pci_dma_ops;
	zpci_map_resources(pdev);

	for (i = 0; i < PCI_BAR_COUNT; i++) {
		res = &pdev->resource[i];
		if (res->parent || !res->flags)
			continue;
		pci_claim_resource(pdev, i);
	}

	return 0;
}