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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aq_set_mac_config {int params; int /*<<< orphan*/  max_frame_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (scalar_t__) ; 
 int I40E_AQ_SET_MAC_CONFIG_CRC_EN ; 
 int I40E_ERR_PARAM ; 
 int /*<<< orphan*/  i40e_aqc_opc_set_mac_config ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_set_mac_config(struct i40e_hw *hw,
				u16 max_frame_size,
				bool crc_en, u16 pacing,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aq_set_mac_config *cmd =
		(struct i40e_aq_set_mac_config *)&desc.params.raw;
	enum i40e_status_code status;

	if (max_frame_size == 0)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_mac_config);

	cmd->max_frame_size = CPU_TO_LE16(max_frame_size);
	cmd->params = ((u8)pacing & 0x0F) << 3;
	if (crc_en)
		cmd->params |= I40E_AQ_SET_MAC_CONFIG_CRC_EN;

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	return status;
}