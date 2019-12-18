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
struct TYPE_2__ {int total_pe_num; int /*<<< orphan*/  reserved_pe_idx; } ;
struct pnv_phb {TYPE_1__ ioda; int /*<<< orphan*/  opal_id; } ;
struct pnv_ioda_pe {unsigned int pe_number; struct pnv_phb* phb; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 unsigned int IODA_INVALID_PE ; 
 unsigned short OPAL_M64_WINDOW_TYPE ; 
 scalar_t__ OPAL_SUCCESS ; 
 int PNV_IODA1_M64_SEGS ; 
 scalar_t__ opal_pci_map_pe_mmio_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int,int) ; 
 int /*<<< orphan*/  pe_warn (struct pnv_ioda_pe*,char*,scalar_t__,unsigned short,int) ; 

__attribute__((used)) static void pnv_ioda_free_pe_seg(struct pnv_ioda_pe *pe,
				 unsigned short win,
				 unsigned int *map)
{
	struct pnv_phb *phb = pe->phb;
	int idx;
	int64_t rc;

	for (idx = 0; idx < phb->ioda.total_pe_num; idx++) {
		if (map[idx] != pe->pe_number)
			continue;

		if (win == OPAL_M64_WINDOW_TYPE)
			rc = opal_pci_map_pe_mmio_window(phb->opal_id,
					phb->ioda.reserved_pe_idx, win,
					idx / PNV_IODA1_M64_SEGS,
					idx % PNV_IODA1_M64_SEGS);
		else
			rc = opal_pci_map_pe_mmio_window(phb->opal_id,
					phb->ioda.reserved_pe_idx, win, 0, idx);

		if (rc != OPAL_SUCCESS)
			pe_warn(pe, "Error %lld unmapping (%d) segment#%d\n",
				rc, win, idx);

		map[idx] = IODA_INVALID_PE;
	}
}