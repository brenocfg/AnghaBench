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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int flags; int /*<<< orphan*/  second_tag; int /*<<< orphan*/  first_tag; int /*<<< orphan*/  switch_tag; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_set_switch_config {void* second_tag; void* first_tag; void* switch_tag; int /*<<< orphan*/  mode; void* valid_flags; void* flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 void* CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int I40E_HW_FLAG_802_1AD_CAPABLE ; 
 int /*<<< orphan*/  i40e_aqc_opc_set_switch_config ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_set_switch_config(struct i40e_hw *hw,
				u16 flags, u16 valid_flags, u8 mode,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_set_switch_config *scfg =
		(struct i40e_aqc_set_switch_config *)&desc.params.raw;
	enum i40e_status_code status;

	i40e_fill_default_direct_cmd_desc(&desc,
					  i40e_aqc_opc_set_switch_config);
	scfg->flags = CPU_TO_LE16(flags);
	scfg->valid_flags = CPU_TO_LE16(valid_flags);
	scfg->mode = mode;
	if (hw->flags & I40E_HW_FLAG_802_1AD_CAPABLE) {
		scfg->switch_tag = CPU_TO_LE16(hw->switch_tag);
		scfg->first_tag = CPU_TO_LE16(hw->first_tag);
		scfg->second_tag = CPU_TO_LE16(hw->second_tag);
	}
	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	return status;
}