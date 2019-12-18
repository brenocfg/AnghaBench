#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct mem_ctl_info {int mc_idx; int /*<<< orphan*/  edac_cap; struct dimm_info** dimms; struct bluefield_edac_priv* pvt_info; } ;
struct dimm_info {int nr_pages; int /*<<< orphan*/  dtype; int /*<<< orphan*/  grain; int /*<<< orphan*/  mtype; int /*<<< orphan*/  edac_mode; } ;
struct bluefield_edac_priv {int dimm_per_mc; int* dimm_ranks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_UNKNOWN ; 
 int /*<<< orphan*/  DEV_X16 ; 
 int /*<<< orphan*/  DEV_X4 ; 
 int /*<<< orphan*/  DEV_X8 ; 
 int /*<<< orphan*/  EDAC_FLAG_NONE ; 
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEM_DDR4 ; 
 int /*<<< orphan*/  MEM_EMPTY ; 
 int /*<<< orphan*/  MEM_LRDDR4 ; 
 int /*<<< orphan*/  MEM_NVDIMM ; 
 int /*<<< orphan*/  MEM_RDDR4 ; 
 int /*<<< orphan*/  MLNX_SIP_GET_DIMM_INFO ; 
 int /*<<< orphan*/  MLXBF_DIMM_INFO__IS_LRDIMM ; 
 int /*<<< orphan*/  MLXBF_DIMM_INFO__IS_NVDIMM ; 
 int /*<<< orphan*/  MLXBF_DIMM_INFO__IS_RDIMM ; 
 int /*<<< orphan*/  MLXBF_DIMM_INFO__PACKAGE_X ; 
 int /*<<< orphan*/  MLXBF_DIMM_INFO__RANKS ; 
 int /*<<< orphan*/  MLXBF_DIMM_INFO__SIZE_GB ; 
 int /*<<< orphan*/  MLXBF_EDAC_ERROR_GRAIN ; 
 int PAGE_SIZE ; 
 int SZ_1G ; 
 int smc_call1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bluefield_edac_init_dimms(struct mem_ctl_info *mci)
{
	struct bluefield_edac_priv *priv = mci->pvt_info;
	int mem_ctrl_idx = mci->mc_idx;
	struct dimm_info *dimm;
	u64 smc_info, smc_arg;
	int is_empty = 1, i;

	for (i = 0; i < priv->dimm_per_mc; i++) {
		dimm = mci->dimms[i];

		smc_arg = mem_ctrl_idx << 16 | i;
		smc_info = smc_call1(MLNX_SIP_GET_DIMM_INFO, smc_arg);

		if (!FIELD_GET(MLXBF_DIMM_INFO__SIZE_GB, smc_info)) {
			dimm->mtype = MEM_EMPTY;
			continue;
		}

		is_empty = 0;

		dimm->edac_mode = EDAC_SECDED;

		if (FIELD_GET(MLXBF_DIMM_INFO__IS_NVDIMM, smc_info))
			dimm->mtype = MEM_NVDIMM;
		else if (FIELD_GET(MLXBF_DIMM_INFO__IS_LRDIMM, smc_info))
			dimm->mtype = MEM_LRDDR4;
		else if (FIELD_GET(MLXBF_DIMM_INFO__IS_RDIMM, smc_info))
			dimm->mtype = MEM_RDDR4;
		else
			dimm->mtype = MEM_DDR4;

		dimm->nr_pages =
			FIELD_GET(MLXBF_DIMM_INFO__SIZE_GB, smc_info) *
			(SZ_1G / PAGE_SIZE);
		dimm->grain = MLXBF_EDAC_ERROR_GRAIN;

		/* Mem controller for BlueField only supports x4, x8 and x16 */
		switch (FIELD_GET(MLXBF_DIMM_INFO__PACKAGE_X, smc_info)) {
		case 4:
			dimm->dtype = DEV_X4;
			break;
		case 8:
			dimm->dtype = DEV_X8;
			break;
		case 16:
			dimm->dtype = DEV_X16;
			break;
		default:
			dimm->dtype = DEV_UNKNOWN;
		}

		priv->dimm_ranks[i] =
			FIELD_GET(MLXBF_DIMM_INFO__RANKS, smc_info);
	}

	if (is_empty)
		mci->edac_cap = EDAC_FLAG_NONE;
	else
		mci->edac_cap = EDAC_FLAG_SECDED;
}