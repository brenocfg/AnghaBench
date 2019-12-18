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
typedef  void* u16 ;
struct i40e_vsi_context {void* vsis_unallocated; void* vsis_allocated; void* vsi_number; void* seid; int /*<<< orphan*/  info; } ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_add_get_update_vsi_completion {int /*<<< orphan*/  vsi_free; int /*<<< orphan*/  vsi_used; int /*<<< orphan*/  vsi_number; int /*<<< orphan*/  seid; } ;
struct i40e_aqc_add_get_update_vsi {int /*<<< orphan*/  uplink_seid; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (void*) ; 
 scalar_t__ I40E_AQ_FLAG_BUF ; 
 int I40E_SUCCESS ; 
 void* LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_vsi_parameters ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_get_vsi_params(struct i40e_hw *hw,
				struct i40e_vsi_context *vsi_ctx,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_add_get_update_vsi *cmd =
		(struct i40e_aqc_add_get_update_vsi *)&desc.params.raw;
	struct i40e_aqc_add_get_update_vsi_completion *resp =
		(struct i40e_aqc_add_get_update_vsi_completion *)
		&desc.params.raw;
	enum i40e_status_code status;

	i40e_fill_default_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_vsi_parameters);

	cmd->uplink_seid = CPU_TO_LE16(vsi_ctx->seid);

	desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_BUF);

	status = i40e_asq_send_command(hw, &desc, &vsi_ctx->info,
				    sizeof(vsi_ctx->info), NULL);

	if (status != I40E_SUCCESS)
		goto aq_get_vsi_params_exit;

	vsi_ctx->seid = LE16_TO_CPU(resp->seid);
	vsi_ctx->vsi_number = LE16_TO_CPU(resp->vsi_number);
	vsi_ctx->vsis_allocated = LE16_TO_CPU(resp->vsi_used);
	vsi_ctx->vsis_unallocated = LE16_TO_CPU(resp->vsi_free);

aq_get_vsi_params_exit:
	return status;
}