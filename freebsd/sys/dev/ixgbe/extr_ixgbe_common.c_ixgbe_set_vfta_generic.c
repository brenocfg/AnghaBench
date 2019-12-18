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
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_ERR_PARAM ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_VFTA (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ixgbe_set_vlvf_generic (struct ixgbe_hw*,int,int,int,int*,int,int) ; 

s32 ixgbe_set_vfta_generic(struct ixgbe_hw *hw, u32 vlan, u32 vind,
			   bool vlan_on, bool vlvf_bypass)
{
	u32 regidx, vfta_delta, vfta;
	s32 ret_val;

	DEBUGFUNC("ixgbe_set_vfta_generic");

	if (vlan > 4095 || vind > 63)
		return IXGBE_ERR_PARAM;

	/*
	 * this is a 2 part operation - first the VFTA, then the
	 * VLVF and VLVFB if VT Mode is set
	 * We don't write the VFTA until we know the VLVF part succeeded.
	 */

	/* Part 1
	 * The VFTA is a bitstring made up of 128 32-bit registers
	 * that enable the particular VLAN id, much like the MTA:
	 *    bits[11-5]: which register
	 *    bits[4-0]:  which bit in the register
	 */
	regidx = vlan / 32;
	vfta_delta = 1 << (vlan % 32);
	vfta = IXGBE_READ_REG(hw, IXGBE_VFTA(regidx));

	/*
	 * vfta_delta represents the difference between the current value
	 * of vfta and the value we want in the register.  Since the diff
	 * is an XOR mask we can just update the vfta using an XOR
	 */
	vfta_delta &= vlan_on ? ~vfta : vfta;
	vfta ^= vfta_delta;

	/* Part 2
	 * Call ixgbe_set_vlvf_generic to set VLVFB and VLVF
	 */
	ret_val = ixgbe_set_vlvf_generic(hw, vlan, vind, vlan_on, &vfta_delta,
					 vfta, vlvf_bypass);
	if (ret_val != IXGBE_SUCCESS) {
		if (vlvf_bypass)
			goto vfta_update;
		return ret_val;
	}

vfta_update:
	/* Update VFTA now that we are ready for traffic */
	if (vfta_delta)
		IXGBE_WRITE_REG(hw, IXGBE_VFTA(regidx), vfta);

	return IXGBE_SUCCESS;
}