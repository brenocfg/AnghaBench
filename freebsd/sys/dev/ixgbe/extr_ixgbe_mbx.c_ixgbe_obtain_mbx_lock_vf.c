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
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_ERR_MBX ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_VFMAILBOX ; 
 int IXGBE_VFMAILBOX_VFU ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int ixgbe_read_v2p_mailbox (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_obtain_mbx_lock_vf(struct ixgbe_hw *hw)
{
	s32 ret_val = IXGBE_ERR_MBX;

	DEBUGFUNC("ixgbe_obtain_mbx_lock_vf");

	/* Take ownership of the buffer */
	IXGBE_WRITE_REG(hw, IXGBE_VFMAILBOX, IXGBE_VFMAILBOX_VFU);

	/* reserve mailbox for vf use */
	if (ixgbe_read_v2p_mailbox(hw) & IXGBE_VFMAILBOX_VFU)
		ret_val = IXGBE_SUCCESS;

	return ret_val;
}