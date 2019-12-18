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
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_set_vsi_promiscuous_modes {void* vlan_tag; void* seid; void* valid_flags; void* promiscuous_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 void* CPU_TO_LE16 (int) ; 
 int I40E_AQC_SET_VSI_PROMISC_MULTICAST ; 
 int I40E_AQC_SET_VSI_VLAN_VALID ; 
 int /*<<< orphan*/  i40e_aqc_opc_set_vsi_promiscuous_modes ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_set_vsi_mc_promisc_on_vlan(struct i40e_hw *hw,
				u16 seid, bool enable, u16 vid,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_set_vsi_promiscuous_modes *cmd =
		(struct i40e_aqc_set_vsi_promiscuous_modes *)&desc.params.raw;
	enum i40e_status_code status;
	u16 flags = 0;

	i40e_fill_default_direct_cmd_desc(&desc,
					i40e_aqc_opc_set_vsi_promiscuous_modes);

	if (enable)
		flags |= I40E_AQC_SET_VSI_PROMISC_MULTICAST;

	cmd->promiscuous_flags = CPU_TO_LE16(flags);
	cmd->valid_flags = CPU_TO_LE16(I40E_AQC_SET_VSI_PROMISC_MULTICAST);
	cmd->seid = CPU_TO_LE16(seid);
	cmd->vlan_tag = CPU_TO_LE16(vid | I40E_AQC_SET_VSI_VLAN_VALID);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	return status;
}