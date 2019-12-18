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
struct pci_dn {TYPE_1__* phb; TYPE_2__* table_group; } ;
struct pci_bus {scalar_t__ self; } ;
struct iommu_table {int /*<<< orphan*/ * it_ops; } ;
struct device_node {struct device_node* sibling; struct device_node* child; struct device_node* parent; } ;
struct TYPE_4__ {struct iommu_table** tables; } ;
struct TYPE_3__ {int dma_window_size; int dma_window_base_cur; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  iommu_init_table (struct iommu_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* iommu_pseries_alloc_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_table_pseries_ops ; 
 int /*<<< orphan*/  iommu_table_setparms (TYPE_1__*,struct device_node*,struct iommu_table*) ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* pci_bus_to_OF_node (struct pci_bus*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void pci_dma_bus_setup_pSeries(struct pci_bus *bus)
{
	struct device_node *dn;
	struct iommu_table *tbl;
	struct device_node *isa_dn, *isa_dn_orig;
	struct device_node *tmp;
	struct pci_dn *pci;
	int children;

	dn = pci_bus_to_OF_node(bus);

	pr_debug("pci_dma_bus_setup_pSeries: setting up bus %pOF\n", dn);

	if (bus->self) {
		/* This is not a root bus, any setup will be done for the
		 * device-side of the bridge in iommu_dev_setup_pSeries().
		 */
		return;
	}
	pci = PCI_DN(dn);

	/* Check if the ISA bus on the system is under
	 * this PHB.
	 */
	isa_dn = isa_dn_orig = of_find_node_by_type(NULL, "isa");

	while (isa_dn && isa_dn != dn)
		isa_dn = isa_dn->parent;

	of_node_put(isa_dn_orig);

	/* Count number of direct PCI children of the PHB. */
	for (children = 0, tmp = dn->child; tmp; tmp = tmp->sibling)
		children++;

	pr_debug("Children: %d\n", children);

	/* Calculate amount of DMA window per slot. Each window must be
	 * a power of two (due to pci_alloc_consistent requirements).
	 *
	 * Keep 256MB aside for PHBs with ISA.
	 */

	if (!isa_dn) {
		/* No ISA/IDE - just set window size and return */
		pci->phb->dma_window_size = 0x80000000ul; /* To be divided */

		while (pci->phb->dma_window_size * children > 0x80000000ul)
			pci->phb->dma_window_size >>= 1;
		pr_debug("No ISA/IDE, window size is 0x%llx\n",
			 pci->phb->dma_window_size);
		pci->phb->dma_window_base_cur = 0;

		return;
	}

	/* If we have ISA, then we probably have an IDE
	 * controller too. Allocate a 128MB table but
	 * skip the first 128MB to avoid stepping on ISA
	 * space.
	 */
	pci->phb->dma_window_size = 0x8000000ul;
	pci->phb->dma_window_base_cur = 0x8000000ul;

	pci->table_group = iommu_pseries_alloc_group(pci->phb->node);
	tbl = pci->table_group->tables[0];

	iommu_table_setparms(pci->phb, dn, tbl);
	tbl->it_ops = &iommu_table_pseries_ops;
	iommu_init_table(tbl, pci->phb->node, 0, 0);

	/* Divide the rest (1.75GB) among the children */
	pci->phb->dma_window_size = 0x80000000ul;
	while (pci->phb->dma_window_size * children > 0x70000000ul)
		pci->phb->dma_window_size >>= 1;

	pr_debug("ISA/IDE, window size is 0x%llx\n", pci->phb->dma_window_size);
}