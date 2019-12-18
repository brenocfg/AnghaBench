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
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_configure_switching_comp_bw_limit {int /*<<< orphan*/  max_bw; void* credit; void* seid; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 void* CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_configure_switching_comp_bw_limit ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_config_switch_comp_bw_limit(struct i40e_hw *hw,
				u16 seid, u16 credit, u8 max_bw,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_configure_switching_comp_bw_limit *cmd =
	  (struct i40e_aqc_configure_switching_comp_bw_limit *)&desc.params.raw;
	enum i40e_status_code status;

	i40e_fill_default_direct_cmd_desc(&desc,
				i40e_aqc_opc_configure_switching_comp_bw_limit);

	cmd->seid = CPU_TO_LE16(seid);
	cmd->credit = CPU_TO_LE16(credit);
	cmd->max_bw = max_bw;

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	return status;
}