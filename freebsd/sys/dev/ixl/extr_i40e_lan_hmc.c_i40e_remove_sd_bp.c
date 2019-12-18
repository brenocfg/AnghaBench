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
typedef  int /*<<< orphan*/  u32 ;
struct i40e_hw {int dummy; } ;
struct i40e_hmc_info {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 scalar_t__ I40E_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ i40e_prep_remove_sd_bp (struct i40e_hmc_info*,int /*<<< orphan*/ ) ; 
 int i40e_remove_sd_bp_new (struct i40e_hw*,struct i40e_hmc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40e_status_code i40e_remove_sd_bp(struct i40e_hw *hw,
					       struct i40e_hmc_info *hmc_info,
					       u32 idx)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;

	if (i40e_prep_remove_sd_bp(hmc_info, idx) == I40E_SUCCESS)
		ret_code = i40e_remove_sd_bp_new(hw, hmc_info, idx, TRUE);

	return ret_code;
}