#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int /*<<< orphan*/  dma_offset; } ;
struct TYPE_5__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct device_node {struct device_node* parent; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  table_group; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 TYPE_3__* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,struct device_node*) ; 
 int /*<<< orphan*/  enable_ddw (struct pci_dev*,struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 

__attribute__((used)) static bool iommu_bypass_supported_pSeriesLP(struct pci_dev *pdev, u64 dma_mask)
{
	struct device_node *dn = pci_device_to_OF_node(pdev), *pdn;
	const __be32 *dma_window = NULL;

	/* only attempt to use a new window if 64-bit DMA is requested */
	if (dma_mask < DMA_BIT_MASK(64))
		return false;

	dev_dbg(&pdev->dev, "node is %pOF\n", dn);

	/*
	 * the device tree might contain the dma-window properties
	 * per-device and not necessarily for the bus. So we need to
	 * search upwards in the tree until we either hit a dma-window
	 * property, OR find a parent with a table already allocated.
	 */
	for (pdn = dn; pdn && PCI_DN(pdn) && !PCI_DN(pdn)->table_group;
			pdn = pdn->parent) {
		dma_window = of_get_property(pdn, "ibm,dma-window", NULL);
		if (dma_window)
			break;
	}

	if (pdn && PCI_DN(pdn)) {
		pdev->dev.archdata.dma_offset = enable_ddw(pdev, pdn);
		if (pdev->dev.archdata.dma_offset)
			return true;
	}

	return false;
}