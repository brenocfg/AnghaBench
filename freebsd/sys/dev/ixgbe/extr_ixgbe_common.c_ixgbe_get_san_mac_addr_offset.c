#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_ERROR_INVALID_STATE ; 
 int /*<<< orphan*/  IXGBE_SAN_MAC_ADDR_PTR ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 ixgbe_get_san_mac_addr_offset(struct ixgbe_hw *hw,
					 u16 *san_mac_offset)
{
	s32 ret_val;

	DEBUGFUNC("ixgbe_get_san_mac_addr_offset");

	/*
	 * First read the EEPROM pointer to see if the MAC addresses are
	 * available.
	 */
	ret_val = hw->eeprom.ops.read(hw, IXGBE_SAN_MAC_ADDR_PTR,
				      san_mac_offset);
	if (ret_val) {
		ERROR_REPORT2(IXGBE_ERROR_INVALID_STATE,
			      "eeprom at offset %d failed",
			      IXGBE_SAN_MAC_ADDR_PTR);
	}

	return ret_val;
}