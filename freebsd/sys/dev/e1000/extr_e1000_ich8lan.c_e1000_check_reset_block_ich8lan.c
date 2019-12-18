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
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_BLK_PHY_RESET ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_ICH_FWSM_RSPCIPHY ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static s32 e1000_check_reset_block_ich8lan(struct e1000_hw *hw)
{
	u32 fwsm;
	bool blocked = FALSE;
	int i = 0;

	DEBUGFUNC("e1000_check_reset_block_ich8lan");

	do {
		fwsm = E1000_READ_REG(hw, E1000_FWSM);
		if (!(fwsm & E1000_ICH_FWSM_RSPCIPHY)) {
			blocked = TRUE;
			msec_delay(10);
			continue;
		}
		blocked = FALSE;
	} while (blocked && (i++ < 30));
	return blocked ? E1000_BLK_PHY_RESET : E1000_SUCCESS;
}