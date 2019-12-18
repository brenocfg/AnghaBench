#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct i40e_hw {int dummy; } ;
struct TYPE_7__ {scalar_t__ va; } ;
struct i40e_hmc_pd_table {int /*<<< orphan*/  pd_entry_virt_mem; int /*<<< orphan*/  ref_cnt; TYPE_3__ pd_page_addr; struct i40e_hmc_pd_entry* pd_entry; } ;
struct TYPE_5__ {struct i40e_hmc_pd_table pd_table; } ;
struct i40e_hmc_sd_entry {scalar_t__ entry_type; TYPE_1__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; scalar_t__ ref_cnt; } ;
struct i40e_hmc_pd_entry {TYPE_4__ bp; int /*<<< orphan*/  rsrc_pg; int /*<<< orphan*/  valid; } ;
struct TYPE_6__ {size_t sd_cnt; struct i40e_hmc_sd_entry* sd_entry; } ;
struct i40e_hmc_info {TYPE_2__ sd_table; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  I40E_DEC_BP_REFCNT (TYPE_4__*) ; 
 int /*<<< orphan*/  I40E_DEC_PD_REFCNT (struct i40e_hmc_pd_table*) ; 
 int /*<<< orphan*/  I40E_DMA_MEM ; 
 int I40E_ERR_INVALID_PAGE_DESC_INDEX ; 
 int I40E_ERR_INVALID_SD_TYPE ; 
 size_t I40E_HMC_PD_CNT_IN_SD ; 
 int /*<<< orphan*/  I40E_INVALIDATE_PF_HMC_PD (struct i40e_hw*,size_t,size_t) ; 
 scalar_t__ I40E_SD_TYPE_PAGED ; 
 int I40E_SUCCESS ; 
 int i40e_free_dma_mem (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_free_virt_mem (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_remove_pd_bp(struct i40e_hw *hw,
					struct i40e_hmc_info *hmc_info,
					u32 idx)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	struct i40e_hmc_pd_entry *pd_entry;
	struct i40e_hmc_pd_table *pd_table;
	struct i40e_hmc_sd_entry *sd_entry;
	u32 sd_idx, rel_pd_idx;
	u64 *pd_addr;

	/* calculate index */
	sd_idx = idx / I40E_HMC_PD_CNT_IN_SD;
	rel_pd_idx = idx % I40E_HMC_PD_CNT_IN_SD;
	if (sd_idx >= hmc_info->sd_table.sd_cnt) {
		ret_code = I40E_ERR_INVALID_PAGE_DESC_INDEX;
		DEBUGOUT("i40e_remove_pd_bp: bad idx\n");
		goto exit;
	}
	sd_entry = &hmc_info->sd_table.sd_entry[sd_idx];
	if (I40E_SD_TYPE_PAGED != sd_entry->entry_type) {
		ret_code = I40E_ERR_INVALID_SD_TYPE;
		DEBUGOUT("i40e_remove_pd_bp: wrong sd_entry type\n");
		goto exit;
	}
	/* get the entry and decrease its ref counter */
	pd_table = &hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
	pd_entry = &pd_table->pd_entry[rel_pd_idx];
	I40E_DEC_BP_REFCNT(&pd_entry->bp);
	if (pd_entry->bp.ref_cnt)
		goto exit;

	/* mark the entry invalid */
	pd_entry->valid = FALSE;
	I40E_DEC_PD_REFCNT(pd_table);
	pd_addr = (u64 *)pd_table->pd_page_addr.va;
	pd_addr += rel_pd_idx;
	i40e_memset(pd_addr, 0, sizeof(u64), I40E_DMA_MEM);
	I40E_INVALIDATE_PF_HMC_PD(hw, sd_idx, idx);

	/* free memory here */
	if (!pd_entry->rsrc_pg)
		ret_code = i40e_free_dma_mem(hw, &(pd_entry->bp.addr));
	if (I40E_SUCCESS != ret_code)
		goto exit;
	if (!pd_table->ref_cnt)
		i40e_free_virt_mem(hw, &pd_table->pd_entry_virt_mem);
exit:
	return ret_code;
}