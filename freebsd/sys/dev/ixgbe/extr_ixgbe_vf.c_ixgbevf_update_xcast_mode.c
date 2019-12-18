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
struct ixgbe_hw {int api_version; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IXGBEVF_XCAST_MODE_ALLMULTI ; 
 scalar_t__ IXGBE_ERR_FEATURE_NOT_SUPPORTED ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int IXGBE_VF_UPDATE_XCAST_MODE ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 int IXGBE_VT_MSGTYPE_NACK ; 
#define  ixgbe_mbox_api_12 129 
#define  ixgbe_mbox_api_13 128 
 scalar_t__ ixgbevf_write_msg_read_ack (struct ixgbe_hw*,int*,int*,int) ; 

s32 ixgbevf_update_xcast_mode(struct ixgbe_hw *hw, int xcast_mode)
{
	u32 msgbuf[2];
	s32 err;

	switch (hw->api_version) {
	case ixgbe_mbox_api_12:
		/* New modes were introduced in 1.3 version */
		if (xcast_mode > IXGBEVF_XCAST_MODE_ALLMULTI)
			return IXGBE_ERR_FEATURE_NOT_SUPPORTED;
		/* Fall through */
	case ixgbe_mbox_api_13:
		break;
	default:
		return IXGBE_ERR_FEATURE_NOT_SUPPORTED;
	}

	msgbuf[0] = IXGBE_VF_UPDATE_XCAST_MODE;
	msgbuf[1] = xcast_mode;

	err = ixgbevf_write_msg_read_ack(hw, msgbuf, msgbuf, 2);
	if (err)
		return err;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;
	if (msgbuf[0] == (IXGBE_VF_UPDATE_XCAST_MODE | IXGBE_VT_MSGTYPE_NACK))
		return IXGBE_ERR_FEATURE_NOT_SUPPORTED;
	return IXGBE_SUCCESS;
}