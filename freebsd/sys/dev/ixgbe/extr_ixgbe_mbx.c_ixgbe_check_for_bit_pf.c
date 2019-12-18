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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_MBX ; 
 int /*<<< orphan*/  IXGBE_MBVFICR (int /*<<< orphan*/ ) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_check_for_bit_pf(struct ixgbe_hw *hw, u32 mask, s32 index)
{
	u32 mbvficr = IXGBE_READ_REG(hw, IXGBE_MBVFICR(index));
	s32 ret_val = IXGBE_ERR_MBX;

	if (mbvficr & mask) {
		ret_val = IXGBE_SUCCESS;
		IXGBE_WRITE_REG(hw, IXGBE_MBVFICR(index), mask);
	}

	return ret_val;
}