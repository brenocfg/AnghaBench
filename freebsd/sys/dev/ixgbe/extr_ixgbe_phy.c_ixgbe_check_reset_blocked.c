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
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IXGBE_ERROR_SOFTWARE ; 
 int /*<<< orphan*/  IXGBE_MMNGC ; 
 int IXGBE_MMNGC_MNG_VETO ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ixgbe_mac_82598EB ; 

s32 ixgbe_check_reset_blocked(struct ixgbe_hw *hw)
{
	u32 mmngc;

	DEBUGFUNC("ixgbe_check_reset_blocked");

	/* If we don't have this bit, it can't be blocking */
	if (hw->mac.type == ixgbe_mac_82598EB)
		return FALSE;

	mmngc = IXGBE_READ_REG(hw, IXGBE_MMNGC);
	if (mmngc & IXGBE_MMNGC_MNG_VETO) {
		ERROR_REPORT1(IXGBE_ERROR_SOFTWARE,
			      "MNG_VETO bit detected.\n");
		return TRUE;
	}

	return FALSE;
}