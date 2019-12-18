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
typedef  unsigned long u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int nr_csrows; struct csrow_info** csrows; } ;
struct dimm_info {unsigned long nr_pages; int grain; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  dtype; int /*<<< orphan*/  mtype; } ;
struct csrow_info {unsigned long first_page; unsigned long last_page; TYPE_1__** channels; } ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_UNKNOWN ; 
 int /*<<< orphan*/  EDAC_NONE ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 scalar_t__ I82860_GBA ; 
 int I82860_GBA_MASK ; 
 int I82860_GBA_SHIFT ; 
 scalar_t__ I82860_MCHCFG ; 
 int /*<<< orphan*/  MEM_RMBS ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,unsigned long) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static void i82860_init_csrows(struct mem_ctl_info *mci, struct pci_dev *pdev)
{
	unsigned long last_cumul_size;
	u16 mchcfg_ddim;	/* DRAM Data Integrity Mode 0=none, 2=edac */
	u16 value;
	u32 cumul_size;
	struct csrow_info *csrow;
	struct dimm_info *dimm;
	int index;

	pci_read_config_word(pdev, I82860_MCHCFG, &mchcfg_ddim);
	mchcfg_ddim = mchcfg_ddim & 0x180;
	last_cumul_size = 0;

	/* The group row boundary (GRA) reg values are boundary address
	 * for each DRAM row with a granularity of 16MB.  GRA regs are
	 * cumulative; therefore GRA15 will contain the total memory contained
	 * in all eight rows.
	 */
	for (index = 0; index < mci->nr_csrows; index++) {
		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		pci_read_config_word(pdev, I82860_GBA + index * 2, &value);
		cumul_size = (value & I82860_GBA_MASK) <<
			(I82860_GBA_SHIFT - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumul_size 0x%x\n", index, cumul_size);

		if (cumul_size == last_cumul_size)
			continue;	/* not populated */

		csrow->first_page = last_cumul_size;
		csrow->last_page = cumul_size - 1;
		dimm->nr_pages = cumul_size - last_cumul_size;
		last_cumul_size = cumul_size;
		dimm->grain = 1 << 12;	/* I82860_EAP has 4KiB reolution */
		dimm->mtype = MEM_RMBS;
		dimm->dtype = DEV_UNKNOWN;
		dimm->edac_mode = mchcfg_ddim ? EDAC_SECDED : EDAC_NONE;
	}
}