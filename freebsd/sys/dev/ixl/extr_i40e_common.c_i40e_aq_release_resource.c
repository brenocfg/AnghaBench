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
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_request_resource {int /*<<< orphan*/  resource_number; int /*<<< orphan*/  resource_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  enum i40e_aq_resources_ids { ____Placeholder_i40e_aq_resources_ids } i40e_aq_resources_ids ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int) ; 
 int /*<<< orphan*/  CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  i40e_aqc_opc_release_resource ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_release_resource(struct i40e_hw *hw,
				enum i40e_aq_resources_ids resource,
				u8 sdp_number,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_request_resource *cmd =
		(struct i40e_aqc_request_resource *)&desc.params.raw;
	enum i40e_status_code status;

	DEBUGFUNC("i40e_aq_release_resource");

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_release_resource);

	cmd->resource_id = CPU_TO_LE16(resource);
	cmd->resource_number = CPU_TO_LE32(sdp_number);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	return status;
}