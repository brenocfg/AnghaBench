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
typedef  scalar_t__ u32 ;
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  I40E_DEBUG_NVM ; 
 int I40E_ERR_TIMEOUT ; 
 int /*<<< orphan*/  I40E_GLNVM_SRCTL ; 
 scalar_t__ I40E_GLNVM_SRCTL_DONE_MASK ; 
 scalar_t__ I40E_SRRD_SRCTL_ATTEMPTS ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i40e_usec_delay (int) ; 
 scalar_t__ rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40e_status_code i40e_poll_sr_srctl_done_bit(struct i40e_hw *hw)
{
	enum i40e_status_code ret_code = I40E_ERR_TIMEOUT;
	u32 srctl, wait_cnt;

	DEBUGFUNC("i40e_poll_sr_srctl_done_bit");

	/* Poll the I40E_GLNVM_SRCTL until the done bit is set */
	for (wait_cnt = 0; wait_cnt < I40E_SRRD_SRCTL_ATTEMPTS; wait_cnt++) {
		srctl = rd32(hw, I40E_GLNVM_SRCTL);
		if (srctl & I40E_GLNVM_SRCTL_DONE_MASK) {
			ret_code = I40E_SUCCESS;
			break;
		}
		i40e_usec_delay(5);
	}
	if (ret_code == I40E_ERR_TIMEOUT)
		i40e_debug(hw, I40E_DEBUG_NVM, "Done bit in GLNVM_SRCTL not set");
	return ret_code;
}