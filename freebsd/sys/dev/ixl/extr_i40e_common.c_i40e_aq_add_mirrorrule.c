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
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ I40E_AQC_MIRROR_RULE_TYPE_ALL_EGRESS ; 
 scalar_t__ I40E_AQC_MIRROR_RULE_TYPE_ALL_INGRESS ; 
 int I40E_ERR_PARAM ; 
 int /*<<< orphan*/  i40e_aqc_opc_add_mirror_rule ; 
 int i40e_mirrorrule_op (struct i40e_hw*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,struct i40e_asq_cmd_details*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

enum i40e_status_code i40e_aq_add_mirrorrule(struct i40e_hw *hw, u16 sw_seid,
			u16 rule_type, u16 dest_vsi, u16 count, __le16 *mr_list,
			struct i40e_asq_cmd_details *cmd_details,
			u16 *rule_id, u16 *rules_used, u16 *rules_free)
{
	if (!(rule_type == I40E_AQC_MIRROR_RULE_TYPE_ALL_INGRESS ||
	    rule_type == I40E_AQC_MIRROR_RULE_TYPE_ALL_EGRESS)) {
		if (count == 0 || !mr_list)
			return I40E_ERR_PARAM;
	}

	return i40e_mirrorrule_op(hw, i40e_aqc_opc_add_mirror_rule, sw_seid,
				  rule_type, dest_vsi, count, mr_list,
				  cmd_details, rule_id, rules_used, rules_free);
}