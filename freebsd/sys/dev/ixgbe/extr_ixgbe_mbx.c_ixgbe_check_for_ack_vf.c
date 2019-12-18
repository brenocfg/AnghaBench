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
struct TYPE_3__ {int /*<<< orphan*/  acks; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct ixgbe_hw {TYPE_2__ mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_ERR_MBX ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_VFMAILBOX_PFACK ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_check_for_bit_vf (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_check_for_ack_vf(struct ixgbe_hw *hw, u16 mbx_id)
{
	s32 ret_val = IXGBE_ERR_MBX;

	UNREFERENCED_1PARAMETER(mbx_id);
	DEBUGFUNC("ixgbe_check_for_ack_vf");

	if (!ixgbe_check_for_bit_vf(hw, IXGBE_VFMAILBOX_PFACK)) {
		ret_val = IXGBE_SUCCESS;
		hw->mbx.stats.acks++;
	}

	return ret_val;
}