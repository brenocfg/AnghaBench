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
struct i40e_aqc_add_veb_completion {int /*<<< orphan*/  veb_seid; } ;
struct i40e_aqc_add_veb {void* veb_flags; int /*<<< orphan*/  enable_tcs; void* downlink_seid; void* uplink_seid; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 void* CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_AQC_ADD_VEB_ENABLE_DISABLE_STATS ; 
 int /*<<< orphan*/  I40E_AQC_ADD_VEB_FLOATING ; 
 int /*<<< orphan*/  I40E_AQC_ADD_VEB_PORT_TYPE_DATA ; 
 int /*<<< orphan*/  I40E_AQC_ADD_VEB_PORT_TYPE_DEFAULT ; 
 int I40E_ERR_PARAM ; 
 int /*<<< orphan*/  LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_add_veb ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_add_veb(struct i40e_hw *hw, u16 uplink_seid,
				u16 downlink_seid, u8 enabled_tc,
				bool default_port, u16 *veb_seid,
				bool enable_stats,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_add_veb *cmd =
		(struct i40e_aqc_add_veb *)&desc.params.raw;
	struct i40e_aqc_add_veb_completion *resp =
		(struct i40e_aqc_add_veb_completion *)&desc.params.raw;
	enum i40e_status_code status;
	u16 veb_flags = 0;

	/* SEIDs need to either both be set or both be 0 for floating VEB */
	if (!!uplink_seid != !!downlink_seid)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_add_veb);

	cmd->uplink_seid = CPU_TO_LE16(uplink_seid);
	cmd->downlink_seid = CPU_TO_LE16(downlink_seid);
	cmd->enable_tcs = enabled_tc;
	if (!uplink_seid)
		veb_flags |= I40E_AQC_ADD_VEB_FLOATING;
	if (default_port)
		veb_flags |= I40E_AQC_ADD_VEB_PORT_TYPE_DEFAULT;
	else
		veb_flags |= I40E_AQC_ADD_VEB_PORT_TYPE_DATA;

	/* reverse logic here: set the bitflag to disable the stats */
	if (!enable_stats)
		veb_flags |= I40E_AQC_ADD_VEB_ENABLE_DISABLE_STATS;

	cmd->veb_flags = CPU_TO_LE16(veb_flags);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	if (!status && veb_seid)
		*veb_seid = LE16_TO_CPU(resp->veb_seid);

	return status;
}