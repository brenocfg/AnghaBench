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
struct i40e_aqc_pfc_ignore {int /*<<< orphan*/  tc_bitmap; int /*<<< orphan*/  command_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQC_PFC_IGNORE_SET ; 
 int /*<<< orphan*/  i40e_aqc_opc_dcb_ignore_pfc ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_dcb_ignore_pfc(struct i40e_hw *hw, u8 tcmap,
				bool request, u8 *tcmap_ret,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_pfc_ignore *cmd_resp =
		(struct i40e_aqc_pfc_ignore *)&desc.params.raw;
	enum i40e_status_code status;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_dcb_ignore_pfc);

	if (request)
		cmd_resp->command_flags = I40E_AQC_PFC_IGNORE_SET;

	cmd_resp->tc_bitmap = tcmap;

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	if (!status) {
		if (tcmap_ret != NULL)
			*tcmap_ret = cmd_resp->tc_bitmap;
	}

	return status;
}