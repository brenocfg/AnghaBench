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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_debug_reg_read_write {int /*<<< orphan*/  value_low; int /*<<< orphan*/  value_high; int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 int I40E_ERR_PARAM ; 
 int I40E_SUCCESS ; 
 scalar_t__ LE32_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_debug_read_reg ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_debug_read_register(struct i40e_hw *hw,
				u32 reg_addr, u64 *reg_val,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_debug_reg_read_write *cmd_resp =
		(struct i40e_aqc_debug_reg_read_write *)&desc.params.raw;
	enum i40e_status_code status;

	if (reg_val == NULL)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_debug_read_reg);

	cmd_resp->address = CPU_TO_LE32(reg_addr);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	if (status == I40E_SUCCESS) {
		*reg_val = ((u64)LE32_TO_CPU(cmd_resp->value_high) << 32) |
			   (u64)LE32_TO_CPU(cmd_resp->value_low);
	}

	return status;
}