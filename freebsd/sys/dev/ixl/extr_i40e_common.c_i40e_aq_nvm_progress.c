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
struct TYPE_2__ {int /*<<< orphan*/ * raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  i40e_aqc_opc_nvm_progress ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_nvm_progress(struct i40e_hw *hw, u8 *progress,
				struct i40e_asq_cmd_details *cmd_details)
{
	enum i40e_status_code status;
	struct i40e_aq_desc desc;

	DEBUGFUNC("i40e_aq_nvm_progress");

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_nvm_progress);
	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);
	*progress = desc.params.raw[0];
	return status;
}