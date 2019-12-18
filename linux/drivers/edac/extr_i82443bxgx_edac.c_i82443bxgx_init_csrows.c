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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int nr_csrows; int /*<<< orphan*/  mc_idx; struct csrow_info** csrows; } ;
struct dimm_info {int nr_pages; int grain; int mtype; int edac_mode; int /*<<< orphan*/  dtype; } ;
struct csrow_info {int first_page; int last_page; TYPE_1__** channels; } ;
typedef  enum mem_type { ____Placeholder_mem_type } mem_type ;
typedef  enum edac_type { ____Placeholder_edac_type } edac_type ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_UNKNOWN ; 
 scalar_t__ I82443BXGX_DRAMC ; 
 scalar_t__ I82443BXGX_DRB ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void i82443bxgx_init_csrows(struct mem_ctl_info *mci,
				struct pci_dev *pdev,
				enum edac_type edac_mode,
				enum mem_type mtype)
{
	struct csrow_info *csrow;
	struct dimm_info *dimm;
	int index;
	u8 drbar, dramc;
	u32 row_base, row_high_limit, row_high_limit_last;

	pci_read_config_byte(pdev, I82443BXGX_DRAMC, &dramc);
	row_high_limit_last = 0;
	for (index = 0; index < mci->nr_csrows; index++) {
		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		pci_read_config_byte(pdev, I82443BXGX_DRB + index, &drbar);
		edac_dbg(1, "MC%d: Row=%d DRB = %#0x\n",
			 mci->mc_idx, index, drbar);
		row_high_limit = ((u32) drbar << 23);
		/* find the DRAM Chip Select Base address and mask */
		edac_dbg(1, "MC%d: Row=%d, Boundary Address=%#0x, Last = %#0x\n",
			 mci->mc_idx, index, row_high_limit,
			 row_high_limit_last);

		/* 440GX goes to 2GB, represented with a DRB of 0. */
		if (row_high_limit_last && !row_high_limit)
			row_high_limit = 1UL << 31;

		/* This row is empty [p.49] */
		if (row_high_limit == row_high_limit_last)
			continue;
		row_base = row_high_limit_last;
		csrow->first_page = row_base >> PAGE_SHIFT;
		csrow->last_page = (row_high_limit >> PAGE_SHIFT) - 1;
		dimm->nr_pages = csrow->last_page - csrow->first_page + 1;
		/* EAP reports in 4kilobyte granularity [61] */
		dimm->grain = 1 << 12;
		dimm->mtype = mtype;
		/* I don't think 440BX can tell you device type? FIXME? */
		dimm->dtype = DEV_UNKNOWN;
		/* Mode is global to all rows on 440BX */
		dimm->edac_mode = edac_mode;
		row_high_limit_last = row_high_limit;
	}
}