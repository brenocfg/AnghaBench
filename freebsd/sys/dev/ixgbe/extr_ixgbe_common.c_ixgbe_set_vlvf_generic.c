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
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_ERR_PARAM ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_VFTA (int) ; 
 int /*<<< orphan*/  IXGBE_VLVF (int) ; 
 int /*<<< orphan*/  IXGBE_VLVFB (int) ; 
 int IXGBE_VLVF_VIEN ; 
 int /*<<< orphan*/  IXGBE_VT_CTL ; 
 int IXGBE_VT_CTL_VT_ENABLE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int ixgbe_find_vlvf_slot (struct ixgbe_hw*,int,int) ; 

s32 ixgbe_set_vlvf_generic(struct ixgbe_hw *hw, u32 vlan, u32 vind,
			   bool vlan_on, u32 *vfta_delta, u32 vfta,
			   bool vlvf_bypass)
{
	u32 bits;
	s32 vlvf_index;

	DEBUGFUNC("ixgbe_set_vlvf_generic");

	if (vlan > 4095 || vind > 63)
		return IXGBE_ERR_PARAM;

	/* If VT Mode is set
	 *   Either vlan_on
	 *     make sure the vlan is in VLVF
	 *     set the vind bit in the matching VLVFB
	 *   Or !vlan_on
	 *     clear the pool bit and possibly the vind
	 */
	if (!(IXGBE_READ_REG(hw, IXGBE_VT_CTL) & IXGBE_VT_CTL_VT_ENABLE))
		return IXGBE_SUCCESS;

	vlvf_index = ixgbe_find_vlvf_slot(hw, vlan, vlvf_bypass);
	if (vlvf_index < 0)
		return vlvf_index;

	bits = IXGBE_READ_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + vind / 32));

	/* set the pool bit */
	bits |= 1 << (vind % 32);
	if (vlan_on)
		goto vlvf_update;

	/* clear the pool bit */
	bits ^= 1 << (vind % 32);

	if (!bits &&
	    !IXGBE_READ_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + 1 - vind / 32))) {
		/* Clear VFTA first, then disable VLVF.  Otherwise
		 * we run the risk of stray packets leaking into
		 * the PF via the default pool
		 */
		if (*vfta_delta)
			IXGBE_WRITE_REG(hw, IXGBE_VFTA(vlan / 32), vfta);

		/* disable VLVF and clear remaining bit from pool */
		IXGBE_WRITE_REG(hw, IXGBE_VLVF(vlvf_index), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + vind / 32), 0);

		return IXGBE_SUCCESS;
	}

	/* If there are still bits set in the VLVFB registers
	 * for the VLAN ID indicated we need to see if the
	 * caller is requesting that we clear the VFTA entry bit.
	 * If the caller has requested that we clear the VFTA
	 * entry bit but there are still pools/VFs using this VLAN
	 * ID entry then ignore the request.  We're not worried
	 * about the case where we're turning the VFTA VLAN ID
	 * entry bit on, only when requested to turn it off as
	 * there may be multiple pools and/or VFs using the
	 * VLAN ID entry.  In that case we cannot clear the
	 * VFTA bit until all pools/VFs using that VLAN ID have also
	 * been cleared.  This will be indicated by "bits" being
	 * zero.
	 */
	*vfta_delta = 0;

vlvf_update:
	/* record pool change and enable VLAN ID if not already enabled */
	IXGBE_WRITE_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + vind / 32), bits);
	IXGBE_WRITE_REG(hw, IXGBE_VLVF(vlvf_index), IXGBE_VLVF_VIEN | vlan);

	return IXGBE_SUCCESS;
}