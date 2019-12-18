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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_EEMNGCTL ; 
 scalar_t__ E1000_ERR_RESET ; 
 int E1000_NVM_CFG_DONE_PORT_0 ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ PHY_CFG_TIMEOUT ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static s32 e1000_get_cfg_done_82571(struct e1000_hw *hw)
{
	s32 timeout = PHY_CFG_TIMEOUT;

	DEBUGFUNC("e1000_get_cfg_done_82571");

	while (timeout) {
		if (E1000_READ_REG(hw, E1000_EEMNGCTL) &
		    E1000_NVM_CFG_DONE_PORT_0)
			break;
		msec_delay(1);
		timeout--;
	}
	if (!timeout) {
		DEBUGOUT("MNG configuration cycle has not completed.\n");
		return -E1000_ERR_RESET;
	}

	return E1000_SUCCESS;
}