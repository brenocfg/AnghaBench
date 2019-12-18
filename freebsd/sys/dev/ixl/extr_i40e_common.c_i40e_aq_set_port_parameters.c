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
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_set_port_parameters {void* command_flags; void* bad_frame_vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 void* CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_AQ_SET_P_PARAMS_DOUBLE_VLAN_ENA ; 
 int /*<<< orphan*/  I40E_AQ_SET_P_PARAMS_PAD_SHORT_PACKETS ; 
 int /*<<< orphan*/  I40E_AQ_SET_P_PARAMS_SAVE_BAD_PACKETS ; 
 int /*<<< orphan*/  i40e_aqc_opc_set_port_parameters ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_set_port_parameters(struct i40e_hw *hw,
				u16 bad_frame_vsi, bool save_bad_pac,
				bool pad_short_pac, bool double_vlan,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aqc_set_port_parameters *cmd;
	enum i40e_status_code status;
	struct i40e_aq_desc desc;
	u16 command_flags = 0;

	cmd = (struct i40e_aqc_set_port_parameters *)&desc.params.raw;

	i40e_fill_default_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_port_parameters);

	cmd->bad_frame_vsi = CPU_TO_LE16(bad_frame_vsi);
	if (save_bad_pac)
		command_flags |= I40E_AQ_SET_P_PARAMS_SAVE_BAD_PACKETS;
	if (pad_short_pac)
		command_flags |= I40E_AQ_SET_P_PARAMS_PAD_SHORT_PACKETS;
	if (double_vlan)
		command_flags |= I40E_AQ_SET_P_PARAMS_DOUBLE_VLAN_ENA;
	cmd->command_flags = CPU_TO_LE16(command_flags);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	return status;
}