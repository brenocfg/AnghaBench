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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_EERD ; 
 int /*<<< orphan*/  E1000_EEWR ; 
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 int E1000_NVM_POLL_READ ; 
 scalar_t__ E1000_NVM_RW_REG_DONE ; 
 scalar_t__ E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 e1000_poll_eerd_eewr_done(struct e1000_hw *hw, int ee_reg)
{
	u32 attempts = 100000;
	u32 i, reg = 0;

	DEBUGFUNC("e1000_poll_eerd_eewr_done");

	for (i = 0; i < attempts; i++) {
		if (ee_reg == E1000_NVM_POLL_READ)
			reg = E1000_READ_REG(hw, E1000_EERD);
		else
			reg = E1000_READ_REG(hw, E1000_EEWR);

		if (reg & E1000_NVM_RW_REG_DONE)
			return E1000_SUCCESS;

		usec_delay(5);
	}

	return -E1000_ERR_NVM;
}