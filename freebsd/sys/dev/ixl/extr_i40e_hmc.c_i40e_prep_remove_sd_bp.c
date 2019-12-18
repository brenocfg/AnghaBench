#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {scalar_t__ ref_cnt; } ;
struct TYPE_4__ {TYPE_3__ bp; } ;
struct i40e_hmc_sd_entry {int /*<<< orphan*/  valid; TYPE_1__ u; } ;
struct TYPE_5__ {struct i40e_hmc_sd_entry* sd_entry; } ;
struct i40e_hmc_info {TYPE_2__ sd_table; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  I40E_DEC_BP_REFCNT (TYPE_3__*) ; 
 int /*<<< orphan*/  I40E_DEC_SD_REFCNT (TYPE_2__*) ; 
 int I40E_ERR_NOT_READY ; 
 int I40E_SUCCESS ; 

enum i40e_status_code i40e_prep_remove_sd_bp(struct i40e_hmc_info *hmc_info,
					     u32 idx)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	struct i40e_hmc_sd_entry *sd_entry;

	/* get the entry and decrease its ref counter */
	sd_entry = &hmc_info->sd_table.sd_entry[idx];
	I40E_DEC_BP_REFCNT(&sd_entry->u.bp);
	if (sd_entry->u.bp.ref_cnt) {
		ret_code = I40E_ERR_NOT_READY;
		goto exit;
	}
	I40E_DEC_SD_REFCNT(&hmc_info->sd_table);

	/* mark the entry invalid */
	sd_entry->valid = FALSE;
exit:
	return ret_code;
}