#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ (* read ) (struct e1000_hw*,int*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* check_for_rst ) (struct e1000_hw*,int /*<<< orphan*/ ) ;} ;
struct e1000_mbx_info {int /*<<< orphan*/  timeout; TYPE_1__ ops; } ;
struct e1000_mac_info {scalar_t__ get_link_status; } ;
struct e1000_hw {struct e1000_mac_info mac; struct e1000_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ERR_MAC_INIT ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int E1000_VT_MSGTYPE_CTS ; 
 int E1000_VT_MSGTYPE_NACK ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct e1000_hw*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_check_for_link_vf(struct e1000_hw *hw)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;
	u32 in_msg = 0;

	DEBUGFUNC("e1000_check_for_link_vf");

	/*
	 * We only want to run this if there has been a rst asserted.
	 * in this case that could mean a link change, device reset,
	 * or a virtual function reset
	 */

	/* If we were hit with a reset or timeout drop the link */
	if (!mbx->ops.check_for_rst(hw, 0) || !mbx->timeout)
		mac->get_link_status = TRUE;

	if (!mac->get_link_status)
		goto out;

	/* if link status is down no point in checking to see if pf is up */
	if (!(E1000_READ_REG(hw, E1000_STATUS) & E1000_STATUS_LU))
		goto out;

	/* if the read failed it could just be a mailbox collision, best wait
	 * until we are called again and don't report an error */
	if (mbx->ops.read(hw, &in_msg, 1, 0))
		goto out;

	/* if incoming message isn't clear to send we are waiting on response */
	if (!(in_msg & E1000_VT_MSGTYPE_CTS)) {
		/* message is not CTS and is NACK we have lost CTS status */
		if (in_msg & E1000_VT_MSGTYPE_NACK)
			ret_val = -E1000_ERR_MAC_INIT;
		goto out;
	}

	/* at this point we know the PF is talking to us, check and see if
	 * we are still accepting timeout or if we had a timeout failure.
	 * if we failed then we will need to reinit */
	if (!mbx->timeout) {
		ret_val = -E1000_ERR_MAC_INIT;
		goto out;
	}

	/* if we passed all the tests above then the link is up and we no
	 * longer need to check for link */
	mac->get_link_status = FALSE;

out:
	return ret_val;
}