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
typedef  int u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int nr_csrows; int /*<<< orphan*/  edac_cap; struct csrow_info** csrows; } ;
struct dimm_info {int nr_pages; int grain; int edac_mode; int /*<<< orphan*/  dtype; int /*<<< orphan*/  mtype; } ;
struct csrow_info {unsigned long first_page; int last_page; TYPE_1__** channels; } ;
typedef  enum edac_type { ____Placeholder_edac_type } edac_type ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_X4 ; 
 int /*<<< orphan*/  DEV_X8 ; 
 int /*<<< orphan*/  E7XXX_DRA ; 
 scalar_t__ E7XXX_DRB ; 
 int /*<<< orphan*/  EDAC_FLAG_S4ECD4ED ; 
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 int EDAC_NONE ; 
 int EDAC_S4ECD4ED ; 
 int EDAC_SECDED ; 
 int /*<<< orphan*/  MEM_RDDR ; 
 int PAGE_SHIFT ; 
 int drb_granularity (int,int) ; 
 int dual_channel_active (int,int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void e7xxx_init_csrows(struct mem_ctl_info *mci, struct pci_dev *pdev,
			int dev_idx, u32 drc)
{
	unsigned long last_cumul_size;
	int index, j;
	u8 value;
	u32 dra, cumul_size, nr_pages;
	int drc_chan, drc_drbg, drc_ddim, mem_dev;
	struct csrow_info *csrow;
	struct dimm_info *dimm;
	enum edac_type edac_mode;

	pci_read_config_dword(pdev, E7XXX_DRA, &dra);
	drc_chan = dual_channel_active(drc, dev_idx);
	drc_drbg = drb_granularity(drc, dev_idx);
	drc_ddim = (drc >> 20) & 0x3;
	last_cumul_size = 0;

	/* The dram row boundary (DRB) reg values are boundary address
	 * for each DRAM row with a granularity of 32 or 64MB (single/dual
	 * channel operation).  DRB regs are cumulative; therefore DRB7 will
	 * contain the total memory contained in all eight rows.
	 */
	for (index = 0; index < mci->nr_csrows; index++) {
		/* mem_dev 0=x8, 1=x4 */
		mem_dev = (dra >> (index * 4 + 3)) & 0x1;
		csrow = mci->csrows[index];

		pci_read_config_byte(pdev, E7XXX_DRB + index, &value);
		/* convert a 64 or 32 MiB DRB to a page size. */
		cumul_size = value << (25 + drc_drbg - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumul_size 0x%x\n", index, cumul_size);
		if (cumul_size == last_cumul_size)
			continue;	/* not populated */

		csrow->first_page = last_cumul_size;
		csrow->last_page = cumul_size - 1;
		nr_pages = cumul_size - last_cumul_size;
		last_cumul_size = cumul_size;

		/*
		* if single channel or x8 devices then SECDED
		* if dual channel and x4 then S4ECD4ED
		*/
		if (drc_ddim) {
			if (drc_chan && mem_dev) {
				edac_mode = EDAC_S4ECD4ED;
				mci->edac_cap |= EDAC_FLAG_S4ECD4ED;
			} else {
				edac_mode = EDAC_SECDED;
				mci->edac_cap |= EDAC_FLAG_SECDED;
			}
		} else
			edac_mode = EDAC_NONE;

		for (j = 0; j < drc_chan + 1; j++) {
			dimm = csrow->channels[j]->dimm;

			dimm->nr_pages = nr_pages / (drc_chan + 1);
			dimm->grain = 1 << 12;	/* 4KiB - resolution of CELOG */
			dimm->mtype = MEM_RDDR;	/* only one type supported */
			dimm->dtype = mem_dev ? DEV_X4 : DEV_X8;
			dimm->edac_mode = edac_mode;
		}
	}
}