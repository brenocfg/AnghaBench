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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CTX_LOCK_HELD (struct e1000_hw*) ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT2 (char*,int,int) ; 
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_EXTCNF_CTRL ; 
 int E1000_EXTCNF_CTRL_SWFLAG ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int PHY_CFG_TIMEOUT ; 
 int SW_FLAG_TIMEOUT ; 
 int /*<<< orphan*/  msec_delay_irq (int) ; 

__attribute__((used)) static s32 e1000_acquire_swflag_ich8lan(struct e1000_hw *hw)
{
	u32 extcnf_ctrl, timeout = PHY_CFG_TIMEOUT;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_acquire_swflag_ich8lan");

	ASSERT_CTX_LOCK_HELD(hw);

	while (timeout) {
		extcnf_ctrl = E1000_READ_REG(hw, E1000_EXTCNF_CTRL);
		if (!(extcnf_ctrl & E1000_EXTCNF_CTRL_SWFLAG))
			break;

		msec_delay_irq(1);
		timeout--;
	}

	if (!timeout) {
		DEBUGOUT("SW has already locked the resource.\n");
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

	timeout = SW_FLAG_TIMEOUT;

	extcnf_ctrl |= E1000_EXTCNF_CTRL_SWFLAG;
	E1000_WRITE_REG(hw, E1000_EXTCNF_CTRL, extcnf_ctrl);

	while (timeout) {
		extcnf_ctrl = E1000_READ_REG(hw, E1000_EXTCNF_CTRL);
		if (extcnf_ctrl & E1000_EXTCNF_CTRL_SWFLAG)
			break;

		msec_delay_irq(1);
		timeout--;
	}

	if (!timeout) {
		DEBUGOUT2("Failed to acquire the semaphore, FW or HW has it: FWSM=0x%8.8x EXTCNF_CTRL=0x%8.8x)\n",
			  E1000_READ_REG(hw, E1000_FWSM), extcnf_ctrl);
		extcnf_ctrl &= ~E1000_EXTCNF_CTRL_SWFLAG;
		E1000_WRITE_REG(hw, E1000_EXTCNF_CTRL, extcnf_ctrl);
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

out:
	return ret_val;
}