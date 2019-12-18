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
typedef  int uint16_t ;
struct pnv_ioda_pe {int pe_number; int tce_bypass_enabled; int /*<<< orphan*/  tce_bypass_base; TYPE_1__* phb; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  opal_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memblock_end_of_DRAM () ; 
 scalar_t__ opal_pci_map_pe_dma_window_real (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_err (struct pnv_ioda_pe*,char*,scalar_t__) ; 
 int /*<<< orphan*/  pe_info (struct pnv_ioda_pe*,char*,char*) ; 
 int /*<<< orphan*/  roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnv_pci_ioda2_set_bypass(struct pnv_ioda_pe *pe, bool enable)
{
	uint16_t window_id = (pe->pe_number << 1 ) + 1;
	int64_t rc;

	pe_info(pe, "%sabling 64-bit DMA bypass\n", enable ? "En" : "Dis");
	if (enable) {
		phys_addr_t top = memblock_end_of_DRAM();

		top = roundup_pow_of_two(top);
		rc = opal_pci_map_pe_dma_window_real(pe->phb->opal_id,
						     pe->pe_number,
						     window_id,
						     pe->tce_bypass_base,
						     top);
	} else {
		rc = opal_pci_map_pe_dma_window_real(pe->phb->opal_id,
						     pe->pe_number,
						     window_id,
						     pe->tce_bypass_base,
						     0);
	}
	if (rc)
		pe_err(pe, "OPAL error %lld configuring bypass window\n", rc);
	else
		pe->tce_bypass_enabled = enable;
}