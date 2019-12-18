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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct i40e_hw {scalar_t__ nvm_wait_opcode; int /*<<< orphan*/  nvm_aq_event_desc; } ;
struct i40e_aq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_NONDMA_TO_NONDMA ; 
 int /*<<< orphan*/  i40e_memcpy (int /*<<< orphan*/ *,struct i40e_aq_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_nvmupd_clear_wait_state (struct i40e_hw*) ; 

void i40e_nvmupd_check_wait_event(struct i40e_hw *hw, u16 opcode,
				  struct i40e_aq_desc *desc)
{
	u32 aq_desc_len = sizeof(struct i40e_aq_desc);

	if (opcode == hw->nvm_wait_opcode) {
		i40e_memcpy(&hw->nvm_aq_event_desc, desc,
			    aq_desc_len, I40E_NONDMA_TO_NONDMA);
		i40e_nvmupd_clear_wait_state(hw);
	}
}