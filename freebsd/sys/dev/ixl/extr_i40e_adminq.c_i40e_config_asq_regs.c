#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  pa; } ;
struct TYPE_5__ {TYPE_1__ desc_buf; int /*<<< orphan*/  bal; int /*<<< orphan*/  bah; int /*<<< orphan*/  len; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct TYPE_6__ {int num_asq_entries; TYPE_2__ asq; } ;
struct i40e_hw {TYPE_3__ aq; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_ERR_ADMIN_QUEUE_ERROR ; 
 int I40E_HI_DWORD (int /*<<< orphan*/ ) ; 
 int I40E_LO_DWORD (int /*<<< orphan*/ ) ; 
 int I40E_PF_ATQLEN_ATQENABLE_MASK ; 
 int I40E_SUCCESS ; 
 int I40E_VF_ATQLEN1_ATQENABLE_MASK ; 
 scalar_t__ i40e_is_vf (struct i40e_hw*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum i40e_status_code i40e_config_asq_regs(struct i40e_hw *hw)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	u32 reg = 0;

	/* Clear Head and Tail */
	wr32(hw, hw->aq.asq.head, 0);
	wr32(hw, hw->aq.asq.tail, 0);

	/* set starting point */
	if (!i40e_is_vf(hw))
		wr32(hw, hw->aq.asq.len, (hw->aq.num_asq_entries |
					  I40E_PF_ATQLEN_ATQENABLE_MASK));
	if (i40e_is_vf(hw))
		wr32(hw, hw->aq.asq.len, (hw->aq.num_asq_entries |
					  I40E_VF_ATQLEN1_ATQENABLE_MASK));
	wr32(hw, hw->aq.asq.bal, I40E_LO_DWORD(hw->aq.asq.desc_buf.pa));
	wr32(hw, hw->aq.asq.bah, I40E_HI_DWORD(hw->aq.asq.desc_buf.pa));

	/* Check one register to verify that config was applied */
	reg = rd32(hw, hw->aq.asq.bal);
	if (reg != I40E_LO_DWORD(hw->aq.asq.desc_buf.pa))
		ret_code = I40E_ERR_ADMIN_QUEUE_ERROR;

	return ret_code;
}