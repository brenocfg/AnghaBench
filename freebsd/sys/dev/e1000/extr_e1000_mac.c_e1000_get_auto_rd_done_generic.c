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
 scalar_t__ AUTO_READ_DONE_TIMEOUT ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_AUTO_RD ; 
 scalar_t__ E1000_ERR_RESET ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 e1000_get_auto_rd_done_generic(struct e1000_hw *hw)
{
	s32 i = 0;

	DEBUGFUNC("e1000_get_auto_rd_done_generic");

	while (i < AUTO_READ_DONE_TIMEOUT) {
		if (E1000_READ_REG(hw, E1000_EECD) & E1000_EECD_AUTO_RD)
			break;
		msec_delay(1);
		i++;
	}

	if (i == AUTO_READ_DONE_TIMEOUT) {
		DEBUGOUT("Auto read by HW from NVM has not completed.\n");
		return -E1000_ERR_RESET;
	}

	return E1000_SUCCESS;
}