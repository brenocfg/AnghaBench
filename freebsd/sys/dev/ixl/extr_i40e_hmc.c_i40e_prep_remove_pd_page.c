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
struct TYPE_4__ {scalar_t__ ref_cnt; } ;
struct TYPE_5__ {TYPE_1__ pd_table; } ;
struct i40e_hmc_sd_entry {int /*<<< orphan*/  valid; TYPE_2__ u; } ;
struct TYPE_6__ {struct i40e_hmc_sd_entry* sd_entry; } ;
struct i40e_hmc_info {TYPE_3__ sd_table; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  I40E_DEC_SD_REFCNT (TYPE_3__*) ; 
 int I40E_ERR_NOT_READY ; 
 int I40E_SUCCESS ; 

enum i40e_status_code i40e_prep_remove_pd_page(struct i40e_hmc_info *hmc_info,
					       u32 idx)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	struct i40e_hmc_sd_entry *sd_entry;

	sd_entry = &hmc_info->sd_table.sd_entry[idx];

	if (sd_entry->u.pd_table.ref_cnt) {
		ret_code = I40E_ERR_NOT_READY;
		goto exit;
	}

	/* mark the entry invalid */
	sd_entry->valid = FALSE;

	I40E_DEC_SD_REFCNT(&hmc_info->sd_table);
exit:
	return ret_code;
}