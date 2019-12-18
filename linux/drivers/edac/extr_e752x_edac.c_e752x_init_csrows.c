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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int nr_csrows; int /*<<< orphan*/  edac_cap; struct csrow_info** csrows; } ;
struct dimm_info {int nr_pages; int grain; int edac_mode; int /*<<< orphan*/  dtype; int /*<<< orphan*/  mtype; } ;
struct csrow_info {unsigned long first_page; int last_page; int nr_channels; TYPE_1__** channels; } ;
typedef  enum edac_type { ____Placeholder_edac_type } edac_type ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_X4 ; 
 int /*<<< orphan*/  DEV_X8 ; 
 scalar_t__ E752X_DRA ; 
 scalar_t__ E752X_DRB ; 
 int /*<<< orphan*/  E752X_DRC ; 
 int /*<<< orphan*/  EDAC_FLAG_S4ECD4ED ; 
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 int EDAC_NONE ; 
 int EDAC_S4ECD4ED ; 
 int EDAC_SECDED ; 
 int /*<<< orphan*/  MEM_RDDR ; 
 int PAGE_SHIFT ; 
 scalar_t__ dual_channel_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 size_t remap_csrow_index (struct mem_ctl_info*,int) ; 

__attribute__((used)) static void e752x_init_csrows(struct mem_ctl_info *mci, struct pci_dev *pdev,
			u16 ddrcsr)
{
	struct csrow_info *csrow;
	enum edac_type edac_mode;
	unsigned long last_cumul_size;
	int index, mem_dev, drc_chan;
	int drc_drbg;		/* DRB granularity 0=64mb, 1=128mb */
	int drc_ddim;		/* DRAM Data Integrity Mode 0=none, 2=edac */
	u8 value;
	u32 dra, drc, cumul_size, i, nr_pages;

	dra = 0;
	for (index = 0; index < 4; index++) {
		u8 dra_reg;
		pci_read_config_byte(pdev, E752X_DRA + index, &dra_reg);
		dra |= dra_reg << (index * 8);
	}
	pci_read_config_dword(pdev, E752X_DRC, &drc);
	drc_chan = dual_channel_active(ddrcsr) ? 1 : 0;
	drc_drbg = drc_chan + 1;	/* 128 in dual mode, 64 in single */
	drc_ddim = (drc >> 20) & 0x3;

	/* The dram row boundary (DRB) reg values are boundary address for
	 * each DRAM row with a granularity of 64 or 128MB (single/dual
	 * channel operation).  DRB regs are cumulative; therefore DRB7 will
	 * contain the total memory contained in all eight rows.
	 */
	for (last_cumul_size = index = 0; index < mci->nr_csrows; index++) {
		/* mem_dev 0=x8, 1=x4 */
		mem_dev = (dra >> (index * 4 + 2)) & 0x3;
		csrow = mci->csrows[remap_csrow_index(mci, index)];

		mem_dev = (mem_dev == 2);
		pci_read_config_byte(pdev, E752X_DRB + index, &value);
		/* convert a 128 or 64 MiB DRB to a page size. */
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
		for (i = 0; i < csrow->nr_channels; i++) {
			struct dimm_info *dimm = csrow->channels[i]->dimm;

			edac_dbg(3, "Initializing rank at (%i,%i)\n", index, i);
			dimm->nr_pages = nr_pages / csrow->nr_channels;
			dimm->grain = 1 << 12;	/* 4KiB - resolution of CELOG */
			dimm->mtype = MEM_RDDR;	/* only one type supported */
			dimm->dtype = mem_dev ? DEV_X4 : DEV_X8;
			dimm->edac_mode = edac_mode;
		}
	}
}