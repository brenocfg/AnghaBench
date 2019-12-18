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
struct TYPE_3__ {int /*<<< orphan*/  m32_pci_base; } ;
struct pnv_phb {TYPE_1__ ioda; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  pgsizes; int /*<<< orphan*/  max_levels; int /*<<< orphan*/  max_dynamic_windows_supported; int /*<<< orphan*/  tce32_size; scalar_t__ tce32_start; } ;
struct pnv_ioda_pe {unsigned long long tce_bypass_base; int flags; int /*<<< orphan*/  pbus; TYPE_2__ table_group; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_TABLE_GROUP_MAX_TABLES ; 
 int PNV_IODA_PE_BUS ; 
 int PNV_IODA_PE_BUS_ALL ; 
 int /*<<< orphan*/  POWERNV_IOMMU_MAX_LEVELS ; 
 int /*<<< orphan*/  pe_info (struct pnv_ioda_pe*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_ioda_parse_tce_sizes (struct pnv_phb*) ; 
 int /*<<< orphan*/  pnv_ioda_setup_bus_dma (struct pnv_ioda_pe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_ops ; 
 scalar_t__ pnv_pci_ioda2_setup_default_config (struct pnv_ioda_pe*) ; 
 int /*<<< orphan*/  pnv_pci_ioda_pe_dma_weight (struct pnv_ioda_pe*) ; 

__attribute__((used)) static void pnv_pci_ioda2_setup_dma_pe(struct pnv_phb *phb,
				       struct pnv_ioda_pe *pe)
{
	int64_t rc;

	if (!pnv_pci_ioda_pe_dma_weight(pe))
		return;

	/* TVE #1 is selected by PCI address bit 59 */
	pe->tce_bypass_base = 1ull << 59;

	/* The PE will reserve all possible 32-bits space */
	pe_info(pe, "Setting up 32-bit TCE table at 0..%08x\n",
		phb->ioda.m32_pci_base);

	/* Setup linux iommu table */
	pe->table_group.tce32_start = 0;
	pe->table_group.tce32_size = phb->ioda.m32_pci_base;
	pe->table_group.max_dynamic_windows_supported =
			IOMMU_TABLE_GROUP_MAX_TABLES;
	pe->table_group.max_levels = POWERNV_IOMMU_MAX_LEVELS;
	pe->table_group.pgsizes = pnv_ioda_parse_tce_sizes(phb);
#ifdef CONFIG_IOMMU_API
	pe->table_group.ops = &pnv_pci_ioda2_ops;
#endif

	rc = pnv_pci_ioda2_setup_default_config(pe);
	if (rc)
		return;

	if (pe->flags & (PNV_IODA_PE_BUS | PNV_IODA_PE_BUS_ALL))
		pnv_ioda_setup_bus_dma(pe, pe->pbus);
}