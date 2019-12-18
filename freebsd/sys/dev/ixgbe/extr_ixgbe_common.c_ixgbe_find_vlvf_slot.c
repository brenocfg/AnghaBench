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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IXGBE_ERROR_SOFTWARE ; 
 int IXGBE_ERR_NO_SPACE ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VLVF (int) ; 
 int IXGBE_VLVF_ENTRIES ; 
 int /*<<< orphan*/  IXGBE_VLVF_VIEN ; 

s32 ixgbe_find_vlvf_slot(struct ixgbe_hw *hw, u32 vlan, bool vlvf_bypass)
{
	s32 regindex, first_empty_slot;
	u32 bits;

	/* short cut the special case */
	if (vlan == 0)
		return 0;

	/* if vlvf_bypass is set we don't want to use an empty slot, we
	 * will simply bypass the VLVF if there are no entries present in the
	 * VLVF that contain our VLAN
	 */
	first_empty_slot = vlvf_bypass ? IXGBE_ERR_NO_SPACE : 0;

	/* add VLAN enable bit for comparison */
	vlan |= IXGBE_VLVF_VIEN;

	/* Search for the vlan id in the VLVF entries. Save off the first empty
	 * slot found along the way.
	 *
	 * pre-decrement loop covering (IXGBE_VLVF_ENTRIES - 1) .. 1
	 */
	for (regindex = IXGBE_VLVF_ENTRIES; --regindex;) {
		bits = IXGBE_READ_REG(hw, IXGBE_VLVF(regindex));
		if (bits == vlan)
			return regindex;
		if (!first_empty_slot && !bits)
			first_empty_slot = regindex;
	}

	/* If we are here then we didn't find the VLAN.  Return first empty
	 * slot we found during our search, else error.
	 */
	if (!first_empty_slot)
		ERROR_REPORT1(IXGBE_ERROR_SOFTWARE, "No space in VLVF.\n");

	return first_empty_slot ? first_empty_slot : IXGBE_ERR_NO_SPACE;
}