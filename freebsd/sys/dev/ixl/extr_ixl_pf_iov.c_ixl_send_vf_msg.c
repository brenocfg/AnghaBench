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
typedef  int /*<<< orphan*/  uint16_t ;
struct ixl_vf {int vf_num; } ;
struct TYPE_2__ {int vf_base_id; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct ixl_pf {struct i40e_hw hw; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VC_DEBUG (struct ixl_pf*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i40e_aq_send_msg_to_vf (struct i40e_hw*,int,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_vc_opcode_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_vc_opcode_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_send_vf_msg(struct ixl_pf *pf, struct ixl_vf *vf, uint16_t op,
    enum i40e_status_code status, void *msg, uint16_t len)
{
	struct i40e_hw *hw;
	int global_vf_id;

	hw = &pf->hw;
	global_vf_id = hw->func_caps.vf_base_id + vf->vf_num;

	I40E_VC_DEBUG(pf, ixl_vc_opcode_level(op),
	    "Sending msg (op=%s[%d], status=%d) to VF-%d\n",
	    ixl_vc_opcode_str(op), op, status, vf->vf_num);

	i40e_aq_send_msg_to_vf(hw, global_vf_id, op, status, msg, len, NULL);
}