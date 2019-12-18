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
typedef  int /*<<< orphan*/  u64 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_an_advt_reg {int /*<<< orphan*/  local_an_reg1; int /*<<< orphan*/  local_an_reg0; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_HI_DWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_LO_DWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_local_advt_reg ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_set_local_advt_reg(struct i40e_hw *hw,
				u64 advt_reg,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_an_advt_reg *cmd =
		(struct i40e_aqc_an_advt_reg *)&desc.params.raw;
	enum i40e_status_code status;

	i40e_fill_default_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_local_advt_reg);

	cmd->local_an_reg0 = CPU_TO_LE32(I40E_LO_DWORD(advt_reg));
	cmd->local_an_reg1 = CPU_TO_LE16(I40E_HI_DWORD(advt_reg));

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	return status;
}