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
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_aqc_add_update_pv_completion {int /*<<< orphan*/  pv_seid; } ;
struct i40e_aqc_add_update_pv {void* connected_seid; void* uplink_seid; void* command_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 void* CPU_TO_LE16 (scalar_t__) ; 
 int I40E_ERR_PARAM ; 
 scalar_t__ LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_add_pv ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_add_pvirt(struct i40e_hw *hw, u16 flags,
				       u16 mac_seid, u16 vsi_seid,
				       u16 *ret_seid)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_add_update_pv *cmd =
		(struct i40e_aqc_add_update_pv *)&desc.params.raw;
	struct i40e_aqc_add_update_pv_completion *resp =
		(struct i40e_aqc_add_update_pv_completion *)&desc.params.raw;
	enum i40e_status_code status;

	if (vsi_seid == 0)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_add_pv);
	cmd->command_flags = CPU_TO_LE16(flags);
	cmd->uplink_seid = CPU_TO_LE16(mac_seid);
	cmd->connected_seid = CPU_TO_LE16(vsi_seid);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, NULL);
	if (!status && ret_seid)
		*ret_seid = LE16_TO_CPU(resp->pv_seid);

	return status;
}