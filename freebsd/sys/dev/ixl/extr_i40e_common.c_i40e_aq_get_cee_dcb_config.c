#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aq_desc {int /*<<< orphan*/  flags; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 scalar_t__ I40E_AQ_FLAG_BUF ; 
 int I40E_ERR_PARAM ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_cee_dcb_cfg ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,void*,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_get_cee_dcb_config(struct i40e_hw *hw,
				void *buff, u16 buff_size,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	enum i40e_status_code status;

	if (buff_size == 0 || !buff)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_get_cee_dcb_cfg);

	desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_BUF);
	status = i40e_asq_send_command(hw, &desc, (void *)buff, buff_size,
				       cmd_details);

	return status;
}