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

/* Variables and functions */
 int IXGBE_ERR_INVALID_ARGUMENT ; 
 int IXGBE_VF_API_NEGOTIATE ; 
 int IXGBE_VT_MSGTYPE_ACK ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 int ixgbevf_write_msg_read_ack (struct ixgbe_hw*,int*,int*,int) ; 

int ixgbevf_negotiate_api_version(struct ixgbe_hw *hw, int api)
{
	int err;
	u32 msg[3];

	/* Negotiate the mailbox API version */
	msg[0] = IXGBE_VF_API_NEGOTIATE;
	msg[1] = api;
	msg[2] = 0;

	err = ixgbevf_write_msg_read_ack(hw, msg, msg, 3);
	if (!err) {
		msg[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		/* Store value and return 0 on success */
		if (msg[0] == (IXGBE_VF_API_NEGOTIATE | IXGBE_VT_MSGTYPE_ACK)) {
			hw->api_version = api;
			return 0;
		}

		err = IXGBE_ERR_INVALID_ARGUMENT;
	}

	return err;
}