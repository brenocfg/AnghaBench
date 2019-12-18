#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct i40e_hw {int dummy; } ;
struct TYPE_10__ {size_t sd_pd_index; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {scalar_t__ va; } ;
struct TYPE_6__ {int /*<<< orphan*/  pd_page_addr; TYPE_3__ pd_entry_virt_mem; struct i40e_hmc_pd_entry* pd_entry; } ;
struct TYPE_7__ {TYPE_5__ bp; TYPE_1__ pd_table; } ;
struct i40e_hmc_sd_entry {int entry_type; TYPE_2__ u; int /*<<< orphan*/  valid; } ;
struct i40e_hmc_pd_entry {int dummy; } ;
struct TYPE_9__ {size_t sd_cnt; struct i40e_hmc_sd_entry* sd_entry; } ;
struct i40e_hmc_info {TYPE_4__ sd_table; } ;
struct i40e_dma_mem {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  enum i40e_sd_entry_type { ____Placeholder_i40e_sd_entry_type } i40e_sd_entry_type ;
typedef  enum i40e_memory_type { ____Placeholder_i40e_memory_type } i40e_memory_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int FALSE ; 
 int I40E_ERR_BAD_PTR ; 
 int I40E_ERR_INVALID_SD_INDEX ; 
 int /*<<< orphan*/  I40E_HMC_PAGED_BP_SIZE ; 
 int /*<<< orphan*/  I40E_HMC_PD_BP_BUF_ALIGNMENT ; 
 int /*<<< orphan*/  I40E_INC_BP_REFCNT (TYPE_5__*) ; 
 int /*<<< orphan*/  I40E_INC_SD_REFCNT (TYPE_4__*) ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_NONDMA ; 
 scalar_t__ I40E_SD_TYPE_DIRECT ; 
 int I40E_SD_TYPE_PAGED ; 
 int I40E_SUCCESS ; 
 int TRUE ; 
 int i40e_allocate_dma_mem (struct i40e_hw*,struct i40e_dma_mem*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_allocate_virt_mem (struct i40e_hw*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  i40e_free_dma_mem (struct i40e_hw*,struct i40e_dma_mem*) ; 
 int i40e_mem_bp_jumbo ; 
 int i40e_mem_pd ; 
 int /*<<< orphan*/  i40e_memcpy (int /*<<< orphan*/ *,struct i40e_dma_mem*,int,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_add_sd_table_entry(struct i40e_hw *hw,
					      struct i40e_hmc_info *hmc_info,
					      u32 sd_index,
					      enum i40e_sd_entry_type type,
					      u64 direct_mode_sz)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	struct i40e_hmc_sd_entry *sd_entry;
	enum   i40e_memory_type mem_type;
	bool dma_mem_alloc_done = FALSE;
	struct i40e_dma_mem mem;
	u64 alloc_len;

	if (NULL == hmc_info->sd_table.sd_entry) {
		ret_code = I40E_ERR_BAD_PTR;
		DEBUGOUT("i40e_add_sd_table_entry: bad sd_entry\n");
		goto exit;
	}

	if (sd_index >= hmc_info->sd_table.sd_cnt) {
		ret_code = I40E_ERR_INVALID_SD_INDEX;
		DEBUGOUT("i40e_add_sd_table_entry: bad sd_index\n");
		goto exit;
	}

	sd_entry = &hmc_info->sd_table.sd_entry[sd_index];
	if (!sd_entry->valid) {
		if (I40E_SD_TYPE_PAGED == type) {
			mem_type = i40e_mem_pd;
			alloc_len = I40E_HMC_PAGED_BP_SIZE;
		} else {
			mem_type = i40e_mem_bp_jumbo;
			alloc_len = direct_mode_sz;
		}

		/* allocate a 4K pd page or 2M backing page */
		ret_code = i40e_allocate_dma_mem(hw, &mem, mem_type, alloc_len,
						 I40E_HMC_PD_BP_BUF_ALIGNMENT);
		if (ret_code)
			goto exit;
		dma_mem_alloc_done = TRUE;
		if (I40E_SD_TYPE_PAGED == type) {
			ret_code = i40e_allocate_virt_mem(hw,
					&sd_entry->u.pd_table.pd_entry_virt_mem,
					sizeof(struct i40e_hmc_pd_entry) * 512);
			if (ret_code)
				goto exit;
			sd_entry->u.pd_table.pd_entry =
				(struct i40e_hmc_pd_entry *)
				sd_entry->u.pd_table.pd_entry_virt_mem.va;
			i40e_memcpy(&sd_entry->u.pd_table.pd_page_addr,
				    &mem, sizeof(struct i40e_dma_mem),
				    I40E_NONDMA_TO_NONDMA);
		} else {
			i40e_memcpy(&sd_entry->u.bp.addr,
				    &mem, sizeof(struct i40e_dma_mem),
				    I40E_NONDMA_TO_NONDMA);
			sd_entry->u.bp.sd_pd_index = sd_index;
		}
		/* initialize the sd entry */
		hmc_info->sd_table.sd_entry[sd_index].entry_type = type;

		/* increment the ref count */
		I40E_INC_SD_REFCNT(&hmc_info->sd_table);
	}
	/* Increment backing page reference count */
	if (I40E_SD_TYPE_DIRECT == sd_entry->entry_type)
		I40E_INC_BP_REFCNT(&sd_entry->u.bp);
exit:
	if (I40E_SUCCESS != ret_code)
		if (dma_mem_alloc_done)
			i40e_free_dma_mem(hw, &mem);

	return ret_code;
}