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
typedef  int u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_MBX ; 
 int IXGBE_VF_SET_LPE ; 
 int IXGBE_VT_MSGTYPE_NACK ; 
 scalar_t__ ixgbevf_write_msg_read_ack (struct ixgbe_hw*,int*,int*,int) ; 

s32 ixgbevf_rlpml_set_vf(struct ixgbe_hw *hw, u16 max_size)
{
	u32 msgbuf[2];
	s32 retval;

	msgbuf[0] = IXGBE_VF_SET_LPE;
	msgbuf[1] = max_size;

	retval = ixgbevf_write_msg_read_ack(hw, msgbuf, msgbuf, 2);
	if (retval)
		return retval;
	if ((msgbuf[0] & IXGBE_VF_SET_LPE) &&
	    (msgbuf[0] & IXGBE_VT_MSGTYPE_NACK))
		return IXGBE_ERR_MBX;

	return 0;
}