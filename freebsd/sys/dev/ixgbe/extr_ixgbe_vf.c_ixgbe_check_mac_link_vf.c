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
struct TYPE_2__ {scalar_t__ (* read ) (struct ixgbe_hw*,int*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* check_for_rst ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct ixgbe_mbx_info {int /*<<< orphan*/  timeout; TYPE_1__ ops; } ;
struct ixgbe_mac_info {scalar_t__ type; scalar_t__ get_link_status; } ;
struct ixgbe_hw {struct ixgbe_mac_info mac; struct ixgbe_mbx_info mbx; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 scalar_t__ FALSE ; 
#define  IXGBE_LINKS_SPEED_100_82599 131 
#define  IXGBE_LINKS_SPEED_10G_82599 130 
#define  IXGBE_LINKS_SPEED_10_X550EM_A 129 
#define  IXGBE_LINKS_SPEED_1G_82599 128 
 int IXGBE_LINKS_SPEED_82599 ; 
 int IXGBE_LINKS_SPEED_NON_STD ; 
 int IXGBE_LINKS_UP ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_100_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_2_5GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_5GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_UNKNOWN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_VFLINKS ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 int IXGBE_VT_MSGTYPE_NACK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int) ; 
 scalar_t__ ixgbe_mac_82599_vf ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 ixgbe_check_mac_link_vf(struct ixgbe_hw *hw, ixgbe_link_speed *speed,
			    bool *link_up, bool autoneg_wait_to_complete)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	struct ixgbe_mac_info *mac = &hw->mac;
	s32 ret_val = IXGBE_SUCCESS;
	u32 links_reg;
	u32 in_msg = 0;
	UNREFERENCED_1PARAMETER(autoneg_wait_to_complete);

	/* If we were hit with a reset drop the link */
	if (!mbx->ops.check_for_rst(hw, 0) || !mbx->timeout)
		mac->get_link_status = TRUE;

	if (!mac->get_link_status)
		goto out;

	/* if link status is down no point in checking to see if pf is up */
	links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);
	if (!(links_reg & IXGBE_LINKS_UP))
		goto out;

	/* for SFP+ modules and DA cables on 82599 it can take up to 500usecs
	 * before the link status is correct
	 */
	if (mac->type == ixgbe_mac_82599_vf) {
		int i;

		for (i = 0; i < 5; i++) {
			usec_delay(100);
			links_reg = IXGBE_READ_REG(hw, IXGBE_VFLINKS);

			if (!(links_reg & IXGBE_LINKS_UP))
				goto out;
		}
	}

	switch (links_reg & IXGBE_LINKS_SPEED_82599) {
	case IXGBE_LINKS_SPEED_10G_82599:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		if (hw->mac.type >= ixgbe_mac_X550) {
			if (links_reg & IXGBE_LINKS_SPEED_NON_STD)
				*speed = IXGBE_LINK_SPEED_2_5GB_FULL;
		}
		break;
	case IXGBE_LINKS_SPEED_1G_82599:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		break;
	case IXGBE_LINKS_SPEED_100_82599:
		*speed = IXGBE_LINK_SPEED_100_FULL;
		if (hw->mac.type == ixgbe_mac_X550) {
			if (links_reg & IXGBE_LINKS_SPEED_NON_STD)
				*speed = IXGBE_LINK_SPEED_5GB_FULL;
		}
		break;
	case IXGBE_LINKS_SPEED_10_X550EM_A:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
		/* Since Reserved in older MAC's */
		if (hw->mac.type >= ixgbe_mac_X550)
			*speed = IXGBE_LINK_SPEED_10_FULL;
		break;
	default:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
	}

	/* if the read failed it could just be a mailbox collision, best wait
	 * until we are called again and don't report an error
	 */
	if (mbx->ops.read(hw, &in_msg, 1, 0))
		goto out;

	if (!(in_msg & IXGBE_VT_MSGTYPE_CTS)) {
		/* msg is not CTS and is NACK we must have lost CTS status */
		if (in_msg & IXGBE_VT_MSGTYPE_NACK)
			ret_val = -1;
		goto out;
	}

	/* the pf is talking, if we timed out in the past we reinit */
	if (!mbx->timeout) {
		ret_val = -1;
		goto out;
	}

	/* if we passed all the tests above then the link is up and we no
	 * longer need to check for link
	 */
	mac->get_link_status = FALSE;

out:
	*link_up = !mac->get_link_status;
	return ret_val;
}