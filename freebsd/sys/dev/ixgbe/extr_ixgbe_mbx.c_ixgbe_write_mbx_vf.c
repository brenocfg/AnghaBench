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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct TYPE_4__ {int /*<<< orphan*/  msgs_tx; } ;
struct TYPE_3__ {TYPE_2__ stats; } ;
struct ixgbe_hw {TYPE_1__ mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_VFMAILBOX ; 
 int /*<<< orphan*/  IXGBE_VFMAILBOX_REQ ; 
 int /*<<< orphan*/  IXGBE_VFMBMEM ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (size_t) ; 
 int /*<<< orphan*/  ixgbe_check_for_ack_vf (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_check_for_msg_vf (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_obtain_mbx_lock_vf (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_write_mbx_vf(struct ixgbe_hw *hw, u32 *msg, u16 size,
			      u16 mbx_id)
{
	s32 ret_val;
	u16 i;

	UNREFERENCED_1PARAMETER(mbx_id);

	DEBUGFUNC("ixgbe_write_mbx_vf");

	/* lock the mailbox to prevent pf/vf race condition */
	ret_val = ixgbe_obtain_mbx_lock_vf(hw);
	if (ret_val)
		goto out_no_write;

	/* flush msg and acks as we are overwriting the message buffer */
	ixgbe_check_for_msg_vf(hw, 0);
	ixgbe_check_for_ack_vf(hw, 0);

	/* copy the caller specified message to the mailbox memory buffer */
	for (i = 0; i < size; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_VFMBMEM, i, msg[i]);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

	/* Drop VFU and interrupt the PF to tell it a message has been sent */
	IXGBE_WRITE_REG(hw, IXGBE_VFMAILBOX, IXGBE_VFMAILBOX_REQ);

out_no_write:
	return ret_val;
}