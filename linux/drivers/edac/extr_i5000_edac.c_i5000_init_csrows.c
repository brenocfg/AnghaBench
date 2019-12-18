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
struct mem_ctl_info {int /*<<< orphan*/  n_layers; int /*<<< orphan*/  dimms; int /*<<< orphan*/  layers; struct i5000_pvt* pvt_info; } ;
struct i5000_pvt {int maxdimmperch; int maxch; TYPE_1__** dimm_info; } ;
struct dimm_info {int grain; int nr_pages; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  dtype; int /*<<< orphan*/  mtype; } ;
struct TYPE_2__ {int megabytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_X4 ; 
 int /*<<< orphan*/  DEV_X8 ; 
 struct dimm_info* EDAC_DIMM_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  EDAC_S8ECD8ED ; 
 int MAX_BRANCHES ; 
 int /*<<< orphan*/  MEM_FB_DDR2 ; 
 int /*<<< orphan*/  MTR_DIMMS_PRESENT (int) ; 
 int MTR_DRAM_WIDTH (int) ; 
 int determine_mtr (struct i5000_pvt*,int,int) ; 

__attribute__((used)) static int i5000_init_csrows(struct mem_ctl_info *mci)
{
	struct i5000_pvt *pvt;
	struct dimm_info *dimm;
	int empty;
	int max_csrows;
	int mtr;
	int csrow_megs;
	int channel;
	int slot;

	pvt = mci->pvt_info;
	max_csrows = pvt->maxdimmperch * 2;

	empty = 1;		/* Assume NO memory */

	/*
	 * FIXME: The memory layout used to map slot/channel into the
	 * real memory architecture is weird: branch+slot are "csrows"
	 * and channel is channel. That required an extra array (dimm_info)
	 * to map the dimms. A good cleanup would be to remove this array,
	 * and do a loop here with branch, channel, slot
	 */
	for (slot = 0; slot < max_csrows; slot++) {
		for (channel = 0; channel < pvt->maxch; channel++) {

			mtr = determine_mtr(pvt, slot, channel);

			if (!MTR_DIMMS_PRESENT(mtr))
				continue;

			dimm = EDAC_DIMM_PTR(mci->layers, mci->dimms, mci->n_layers,
				       channel / MAX_BRANCHES,
				       channel % MAX_BRANCHES, slot);

			csrow_megs = pvt->dimm_info[slot][channel].megabytes;
			dimm->grain = 8;

			/* Assume DDR2 for now */
			dimm->mtype = MEM_FB_DDR2;

			/* ask what device type on this row */
			if (MTR_DRAM_WIDTH(mtr) == 8)
				dimm->dtype = DEV_X8;
			else
				dimm->dtype = DEV_X4;

			dimm->edac_mode = EDAC_S8ECD8ED;
			dimm->nr_pages = csrow_megs << 8;
		}

		empty = 0;
	}

	return empty;
}