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
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_switch_resource_alloc_element_resp {int dummy; } ;
struct i40e_aqc_get_switch_resource_alloc {int /*<<< orphan*/  num_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int) ; 
 scalar_t__ I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_LB ; 
 int I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_switch_resource_alloc ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,struct i40e_aqc_switch_resource_alloc_element_resp*,int,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_get_switch_resource_alloc(struct i40e_hw *hw,
			u8 *num_entries,
			struct i40e_aqc_switch_resource_alloc_element_resp *buf,
			u16 count,
			struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_get_switch_resource_alloc *cmd_resp =
		(struct i40e_aqc_get_switch_resource_alloc *)&desc.params.raw;
	enum i40e_status_code status;
	u16 length = count * sizeof(*buf);

	i40e_fill_default_direct_cmd_desc(&desc,
					i40e_aqc_opc_get_switch_resource_alloc);

	desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_BUF);
	if (length > I40E_AQ_LARGE_BUF)
		desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_LB);

	status = i40e_asq_send_command(hw, &desc, buf, length, cmd_details);

	if (!status && num_entries)
		*num_entries = cmd_resp->num_entries;

	return status;
}