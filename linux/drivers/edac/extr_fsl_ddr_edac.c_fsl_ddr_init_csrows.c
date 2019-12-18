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
typedef  int u32 ;
struct mem_ctl_info {int nr_csrows; struct csrow_info** csrows; struct fsl_mc_pdata* pvt_info; } ;
struct fsl_mc_pdata {scalar_t__ mc_vbase; } ;
struct dimm_info {int nr_pages; int grain; int mtype; int /*<<< orphan*/  edac_mode; int /*<<< orphan*/  dtype; } ;
struct csrow_info {int first_page; int last_page; TYPE_1__** channels; } ;
typedef  enum mem_type { ____Placeholder_mem_type } mem_type ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_UNKNOWN ; 
 int /*<<< orphan*/  DEV_X32 ; 
 int DSC_RD_EN ; 
 int DSC_SDTYPE_MASK ; 
 int DSC_X32_EN ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 scalar_t__ FSL_MC_CS_BNDS_0 ; 
 int FSL_MC_CS_BNDS_OFS ; 
 scalar_t__ FSL_MC_DDR_SDRAM_CFG ; 
 int MEM_DDR ; 
 int MEM_DDR2 ; 
 int MEM_DDR3 ; 
 int MEM_DDR4 ; 
 int MEM_RDDR ; 
 int MEM_RDDR2 ; 
 int MEM_RDDR3 ; 
 int MEM_RDDR4 ; 
 int MEM_UNKNOWN ; 
 int PAGE_SHIFT ; 
 int ddr_in32 (scalar_t__) ; 

__attribute__((used)) static void fsl_ddr_init_csrows(struct mem_ctl_info *mci)
{
	struct fsl_mc_pdata *pdata = mci->pvt_info;
	struct csrow_info *csrow;
	struct dimm_info *dimm;
	u32 sdram_ctl;
	u32 sdtype;
	enum mem_type mtype;
	u32 cs_bnds;
	int index;

	sdram_ctl = ddr_in32(pdata->mc_vbase + FSL_MC_DDR_SDRAM_CFG);

	sdtype = sdram_ctl & DSC_SDTYPE_MASK;
	if (sdram_ctl & DSC_RD_EN) {
		switch (sdtype) {
		case 0x02000000:
			mtype = MEM_RDDR;
			break;
		case 0x03000000:
			mtype = MEM_RDDR2;
			break;
		case 0x07000000:
			mtype = MEM_RDDR3;
			break;
		case 0x05000000:
			mtype = MEM_RDDR4;
			break;
		default:
			mtype = MEM_UNKNOWN;
			break;
		}
	} else {
		switch (sdtype) {
		case 0x02000000:
			mtype = MEM_DDR;
			break;
		case 0x03000000:
			mtype = MEM_DDR2;
			break;
		case 0x07000000:
			mtype = MEM_DDR3;
			break;
		case 0x05000000:
			mtype = MEM_DDR4;
			break;
		default:
			mtype = MEM_UNKNOWN;
			break;
		}
	}

	for (index = 0; index < mci->nr_csrows; index++) {
		u32 start;
		u32 end;

		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		cs_bnds = ddr_in32(pdata->mc_vbase + FSL_MC_CS_BNDS_0 +
				   (index * FSL_MC_CS_BNDS_OFS));

		start = (cs_bnds & 0xffff0000) >> 16;
		end   = (cs_bnds & 0x0000ffff);

		if (start == end)
			continue;	/* not populated */

		start <<= (24 - PAGE_SHIFT);
		end   <<= (24 - PAGE_SHIFT);
		end    |= (1 << (24 - PAGE_SHIFT)) - 1;

		csrow->first_page = start;
		csrow->last_page = end;

		dimm->nr_pages = end + 1 - start;
		dimm->grain = 8;
		dimm->mtype = mtype;
		dimm->dtype = DEV_UNKNOWN;
		if (sdram_ctl & DSC_X32_EN)
			dimm->dtype = DEV_X32;
		dimm->edac_mode = EDAC_SECDED;
	}
}