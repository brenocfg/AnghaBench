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
struct TYPE_2__ {scalar_t__ group; struct iommu_table** tables; } ;
struct pnv_ioda_pe {TYPE_1__ table_group; } ;
struct iommu_table {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  iommu_group_put (scalar_t__) ; 
 int /*<<< orphan*/  iommu_tce_table_put (struct iommu_table*) ; 
 int /*<<< orphan*/  pe_warn (struct pnv_ioda_pe*,char*,scalar_t__) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_set_bypass (struct pnv_ioda_pe*,int) ; 
 scalar_t__ pnv_pci_ioda2_unset_window (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int pnv_pci_ioda_pe_dma_weight (struct pnv_ioda_pe*) ; 

__attribute__((used)) static void pnv_pci_ioda2_release_pe_dma(struct pnv_ioda_pe *pe)
{
	struct iommu_table *tbl = pe->table_group.tables[0];
	unsigned int weight = pnv_pci_ioda_pe_dma_weight(pe);
#ifdef CONFIG_IOMMU_API
	int64_t rc;
#endif

	if (!weight)
		return;

#ifdef CONFIG_IOMMU_API
	rc = pnv_pci_ioda2_unset_window(&pe->table_group, 0);
	if (rc)
		pe_warn(pe, "OPAL error %lld release DMA window\n", rc);
#endif

	pnv_pci_ioda2_set_bypass(pe, false);
	if (pe->table_group.group) {
		iommu_group_put(pe->table_group.group);
		WARN_ON(pe->table_group.group);
	}

	iommu_tce_table_put(tbl);
}