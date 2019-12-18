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
struct pci_dn {struct device_node* table_group; TYPE_1__* phb; } ;
struct pci_bus {int dummy; } ;
struct iommu_table {int /*<<< orphan*/ * it_ops; } ;
struct device_node {struct iommu_table** tables; struct device_node* parent; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  iommu_init_table (struct iommu_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* iommu_pseries_alloc_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_register_group (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_table_lpar_multi_ops ; 
 int /*<<< orphan*/  iommu_table_setparms_lpar (TYPE_1__*,struct device_node*,struct iommu_table*,struct device_node*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_bus_to_OF_node (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void pci_dma_bus_setup_pSeriesLP(struct pci_bus *bus)
{
	struct iommu_table *tbl;
	struct device_node *dn, *pdn;
	struct pci_dn *ppci;
	const __be32 *dma_window = NULL;

	dn = pci_bus_to_OF_node(bus);

	pr_debug("pci_dma_bus_setup_pSeriesLP: setting up bus %pOF\n",
		 dn);

	/* Find nearest ibm,dma-window, walking up the device tree */
	for (pdn = dn; pdn != NULL; pdn = pdn->parent) {
		dma_window = of_get_property(pdn, "ibm,dma-window", NULL);
		if (dma_window != NULL)
			break;
	}

	if (dma_window == NULL) {
		pr_debug("  no ibm,dma-window property !\n");
		return;
	}

	ppci = PCI_DN(pdn);

	pr_debug("  parent is %pOF, iommu_table: 0x%p\n",
		 pdn, ppci->table_group);

	if (!ppci->table_group) {
		ppci->table_group = iommu_pseries_alloc_group(ppci->phb->node);
		tbl = ppci->table_group->tables[0];
		iommu_table_setparms_lpar(ppci->phb, pdn, tbl,
				ppci->table_group, dma_window);
		tbl->it_ops = &iommu_table_lpar_multi_ops;
		iommu_init_table(tbl, ppci->phb->node, 0, 0);
		iommu_register_group(ppci->table_group,
				pci_domain_nr(bus), 0);
		pr_debug("  created table: %p\n", ppci->table_group);
	}
}