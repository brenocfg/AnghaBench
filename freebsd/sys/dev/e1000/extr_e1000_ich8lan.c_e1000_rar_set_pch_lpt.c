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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int rar_entry_count; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_WLOCK_MAC_MASK ; 
 int E1000_FWSM_WLOCK_MAC_SHIFT ; 
 int /*<<< orphan*/  E1000_RAH (int) ; 
 int E1000_RAH_AV ; 
 int /*<<< orphan*/  E1000_RAL (int) ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SHRAH_PCH_LPT (int) ; 
 int /*<<< orphan*/  E1000_SHRAL_PCH_LPT (int) ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_acquire_swflag_ich8lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_release_swflag_ich8lan (struct e1000_hw*) ; 

__attribute__((used)) static int e1000_rar_set_pch_lpt(struct e1000_hw *hw, u8 *addr, u32 index)
{
	u32 rar_low, rar_high;
	u32 wlock_mac;

	DEBUGFUNC("e1000_rar_set_pch_lpt");

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32) addr[0] | ((u32) addr[1] << 8) |
		   ((u32) addr[2] << 16) | ((u32) addr[3] << 24));

	rar_high = ((u32) addr[4] | ((u32) addr[5] << 8));

	/* If MAC address zero, no need to set the AV bit */
	if (rar_low || rar_high)
		rar_high |= E1000_RAH_AV;

	if (index == 0) {
		E1000_WRITE_REG(hw, E1000_RAL(index), rar_low);
		E1000_WRITE_FLUSH(hw);
		E1000_WRITE_REG(hw, E1000_RAH(index), rar_high);
		E1000_WRITE_FLUSH(hw);
		return E1000_SUCCESS;
	}

	/* The manageability engine (ME) can lock certain SHRAR registers that
	 * it is using - those registers are unavailable for use.
	 */
	if (index < hw->mac.rar_entry_count) {
		wlock_mac = E1000_READ_REG(hw, E1000_FWSM) &
			    E1000_FWSM_WLOCK_MAC_MASK;
		wlock_mac >>= E1000_FWSM_WLOCK_MAC_SHIFT;

		/* Check if all SHRAR registers are locked */
		if (wlock_mac == 1)
			goto out;

		if ((wlock_mac == 0) || (index <= wlock_mac)) {
			s32 ret_val;

			ret_val = e1000_acquire_swflag_ich8lan(hw);

			if (ret_val)
				goto out;

			E1000_WRITE_REG(hw, E1000_SHRAL_PCH_LPT(index - 1),
					rar_low);
			E1000_WRITE_FLUSH(hw);
			E1000_WRITE_REG(hw, E1000_SHRAH_PCH_LPT(index - 1),
					rar_high);
			E1000_WRITE_FLUSH(hw);

			e1000_release_swflag_ich8lan(hw);

			/* verify the register updates */
			if ((E1000_READ_REG(hw, E1000_SHRAL_PCH_LPT(index - 1)) == rar_low) &&
			    (E1000_READ_REG(hw, E1000_SHRAH_PCH_LPT(index - 1)) == rar_high))
				return E1000_SUCCESS;
		}
	}

out:
	DEBUGOUT1("Failed to write receive address at index %d\n", index);
	return -E1000_ERR_CONFIG;
}