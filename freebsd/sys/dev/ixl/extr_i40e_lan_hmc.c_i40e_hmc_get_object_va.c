#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_9__ {struct i40e_hmc_sd_entry* sd_entry; } ;
struct i40e_hmc_info {scalar_t__ signature; TYPE_2__* hmc_obj; TYPE_1__ sd_table; } ;
struct i40e_hw {struct i40e_hmc_info hmc; } ;
struct TYPE_14__ {scalar_t__ va; } ;
struct TYPE_15__ {TYPE_6__ addr; } ;
struct TYPE_11__ {struct i40e_hmc_pd_entry* pd_entry; } ;
struct TYPE_16__ {TYPE_7__ bp; TYPE_3__ pd_table; } ;
struct i40e_hmc_sd_entry {scalar_t__ entry_type; TYPE_8__ u; } ;
struct TYPE_12__ {scalar_t__ va; } ;
struct TYPE_13__ {TYPE_4__ addr; } ;
struct i40e_hmc_pd_entry {TYPE_5__ bp; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  enum i40e_hmc_lan_rsrc_type { ____Placeholder_i40e_hmc_lan_rsrc_type } i40e_hmc_lan_rsrc_type ;
struct TYPE_10__ {size_t cnt; int base; size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int I40E_ERR_BAD_PTR ; 
 int I40E_ERR_INVALID_HMC_OBJ_INDEX ; 
 int /*<<< orphan*/  I40E_FIND_PD_INDEX_LIMIT (struct i40e_hmc_info*,int,size_t,int,size_t*,size_t*) ; 
 int /*<<< orphan*/  I40E_FIND_SD_INDEX_LIMIT (struct i40e_hmc_info*,int,size_t,int,size_t*,size_t*) ; 
 int I40E_HMC_DIRECT_BP_SIZE ; 
 scalar_t__ I40E_HMC_INFO_SIGNATURE ; 
 int I40E_HMC_PAGED_BP_SIZE ; 
 size_t I40E_HMC_PD_CNT_IN_SD ; 
 scalar_t__ I40E_SD_TYPE_PAGED ; 
 int I40E_SUCCESS ; 

__attribute__((used)) static
enum i40e_status_code i40e_hmc_get_object_va(struct i40e_hw *hw,
					u8 **object_base,
					enum i40e_hmc_lan_rsrc_type rsrc_type,
					u32 obj_idx)
{
	u32 obj_offset_in_sd, obj_offset_in_pd;
	struct i40e_hmc_info     *hmc_info = &hw->hmc;
	struct i40e_hmc_sd_entry *sd_entry;
	struct i40e_hmc_pd_entry *pd_entry;
	u32 pd_idx, pd_lmt, rel_pd_idx;
	enum i40e_status_code ret_code = I40E_SUCCESS;
	u64 obj_offset_in_fpm;
	u32 sd_idx, sd_lmt;

	if (NULL == hmc_info->hmc_obj) {
		ret_code = I40E_ERR_BAD_PTR;
		DEBUGOUT("i40e_hmc_get_object_va: bad hmc_info->hmc_obj ptr\n");
		goto exit;
	}
	if (NULL == object_base) {
		ret_code = I40E_ERR_BAD_PTR;
		DEBUGOUT("i40e_hmc_get_object_va: bad object_base ptr\n");
		goto exit;
	}
	if (I40E_HMC_INFO_SIGNATURE != hmc_info->signature) {
		ret_code = I40E_ERR_BAD_PTR;
		DEBUGOUT("i40e_hmc_get_object_va: bad hmc_info->signature\n");
		goto exit;
	}
	if (obj_idx >= hmc_info->hmc_obj[rsrc_type].cnt) {
		DEBUGOUT1("i40e_hmc_get_object_va: returns error %d\n",
			  ret_code);
		ret_code = I40E_ERR_INVALID_HMC_OBJ_INDEX;
		goto exit;
	}
	/* find sd index and limit */
	I40E_FIND_SD_INDEX_LIMIT(hmc_info, rsrc_type, obj_idx, 1,
				 &sd_idx, &sd_lmt);

	sd_entry = &hmc_info->sd_table.sd_entry[sd_idx];
	obj_offset_in_fpm = hmc_info->hmc_obj[rsrc_type].base +
			    hmc_info->hmc_obj[rsrc_type].size * obj_idx;

	if (I40E_SD_TYPE_PAGED == sd_entry->entry_type) {
		I40E_FIND_PD_INDEX_LIMIT(hmc_info, rsrc_type, obj_idx, 1,
					 &pd_idx, &pd_lmt);
		rel_pd_idx = pd_idx % I40E_HMC_PD_CNT_IN_SD;
		pd_entry = &sd_entry->u.pd_table.pd_entry[rel_pd_idx];
		obj_offset_in_pd = (u32)(obj_offset_in_fpm %
					 I40E_HMC_PAGED_BP_SIZE);
		*object_base = (u8 *)pd_entry->bp.addr.va + obj_offset_in_pd;
	} else {
		obj_offset_in_sd = (u32)(obj_offset_in_fpm %
					 I40E_HMC_DIRECT_BP_SIZE);
		*object_base = (u8 *)sd_entry->u.bp.addr.va + obj_offset_in_sd;
	}
exit:
	return ret_code;
}