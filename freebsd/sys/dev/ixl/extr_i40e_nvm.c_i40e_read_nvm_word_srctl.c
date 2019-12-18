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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ sr_size; } ;
struct i40e_hw {TYPE_1__ nvm; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  I40E_DEBUG_NVM ; 
 int I40E_ERR_PARAM ; 
 int I40E_ERR_TIMEOUT ; 
 int /*<<< orphan*/  I40E_GLNVM_SRCTL ; 
 int I40E_GLNVM_SRCTL_ADDR_SHIFT ; 
 int /*<<< orphan*/  I40E_GLNVM_SRCTL_START_SHIFT ; 
 int /*<<< orphan*/  I40E_GLNVM_SRDATA ; 
 int I40E_GLNVM_SRDATA_RDDATA_MASK ; 
 int I40E_GLNVM_SRDATA_RDDATA_SHIFT ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int i40e_poll_sr_srctl_done_bit (struct i40e_hw*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

enum i40e_status_code i40e_read_nvm_word_srctl(struct i40e_hw *hw, u16 offset,
					       u16 *data)
{
	enum i40e_status_code ret_code = I40E_ERR_TIMEOUT;
	u32 sr_reg;

	DEBUGFUNC("i40e_read_nvm_word_srctl");

	if (offset >= hw->nvm.sr_size) {
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM read error: Offset %d beyond Shadow RAM limit %d\n",
			   offset, hw->nvm.sr_size);
		ret_code = I40E_ERR_PARAM;
		goto read_nvm_exit;
	}

	/* Poll the done bit first */
	ret_code = i40e_poll_sr_srctl_done_bit(hw);
	if (ret_code == I40E_SUCCESS) {
		/* Write the address and start reading */
		sr_reg = ((u32)offset << I40E_GLNVM_SRCTL_ADDR_SHIFT) |
			 BIT(I40E_GLNVM_SRCTL_START_SHIFT);
		wr32(hw, I40E_GLNVM_SRCTL, sr_reg);

		/* Poll I40E_GLNVM_SRCTL until the done bit is set */
		ret_code = i40e_poll_sr_srctl_done_bit(hw);
		if (ret_code == I40E_SUCCESS) {
			sr_reg = rd32(hw, I40E_GLNVM_SRDATA);
			*data = (u16)((sr_reg &
				       I40E_GLNVM_SRDATA_RDDATA_MASK)
				    >> I40E_GLNVM_SRDATA_RDDATA_SHIFT);
		}
	}
	if (ret_code != I40E_SUCCESS)
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM read error: Couldn't access Shadow RAM address: 0x%x\n",
			   offset);

read_nvm_exit:
	return ret_code;
}