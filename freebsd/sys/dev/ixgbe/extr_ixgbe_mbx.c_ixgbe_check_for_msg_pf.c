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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  reqs; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct ixgbe_hw {TYPE_2__ mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_ERR_MBX ; 
 int /*<<< orphan*/  IXGBE_MBVFICR_INDEX (int) ; 
 int IXGBE_MBVFICR_VFREQ_VF1 ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_check_for_bit_pf (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_check_for_msg_pf(struct ixgbe_hw *hw, u16 vf_number)
{
	s32 ret_val = IXGBE_ERR_MBX;
	s32 index = IXGBE_MBVFICR_INDEX(vf_number);
	u32 vf_bit = vf_number % 16;

	DEBUGFUNC("ixgbe_check_for_msg_pf");

	if (!ixgbe_check_for_bit_pf(hw, IXGBE_MBVFICR_VFREQ_VF1 << vf_bit,
				    index)) {
		ret_val = IXGBE_SUCCESS;
		hw->mbx.stats.reqs++;
	}

	return ret_val;
}