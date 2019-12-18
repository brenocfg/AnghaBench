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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int type; scalar_t__ max_link_up_time; } ;
struct ixgbe_hw {int /*<<< orphan*/  device_id; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT2 (char*,scalar_t__,scalar_t__) ; 
 void* FALSE ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T_L ; 
 int /*<<< orphan*/  IXGBE_ESDP ; 
 scalar_t__ IXGBE_ESDP_SDP0 ; 
 scalar_t__ IXGBE_ESDP_SDP2 ; 
 int /*<<< orphan*/  IXGBE_LINKS ; 
#define  IXGBE_LINKS_SPEED_100_82599 134 
#define  IXGBE_LINKS_SPEED_10G_82599 133 
#define  IXGBE_LINKS_SPEED_10_X550EM_A 132 
#define  IXGBE_LINKS_SPEED_1G_82599 131 
 scalar_t__ IXGBE_LINKS_SPEED_82599 ; 
 scalar_t__ IXGBE_LINKS_SPEED_NON_STD ; 
 scalar_t__ IXGBE_LINKS_UP ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_100_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_2_5GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_5GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_UNKNOWN ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int TRUE ; 
#define  ixgbe_mac_82599EB 130 
 int ixgbe_mac_X550 ; 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 
 scalar_t__ ixgbe_need_crosstalk_fix (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 ixgbe_check_mac_link_generic(struct ixgbe_hw *hw, ixgbe_link_speed *speed,
				 bool *link_up, bool link_up_wait_to_complete)
{
	u32 links_reg, links_orig;
	u32 i;

	DEBUGFUNC("ixgbe_check_mac_link_generic");

	/* If Crosstalk fix enabled do the sanity check of making sure
	 * the SFP+ cage is full.
	 */
	if (ixgbe_need_crosstalk_fix(hw)) {
		u32 sfp_cage_full;

		switch (hw->mac.type) {
		case ixgbe_mac_82599EB:
			sfp_cage_full = IXGBE_READ_REG(hw, IXGBE_ESDP) &
					IXGBE_ESDP_SDP2;
			break;
		case ixgbe_mac_X550EM_x:
		case ixgbe_mac_X550EM_a:
			sfp_cage_full = IXGBE_READ_REG(hw, IXGBE_ESDP) &
					IXGBE_ESDP_SDP0;
			break;
		default:
			/* sanity check - No SFP+ devices here */
			sfp_cage_full = FALSE;
			break;
		}

		if (!sfp_cage_full) {
			*link_up = FALSE;
			*speed = IXGBE_LINK_SPEED_UNKNOWN;
			return IXGBE_SUCCESS;
		}
	}

	/* clear the old state */
	links_orig = IXGBE_READ_REG(hw, IXGBE_LINKS);

	links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);

	if (links_orig != links_reg) {
		DEBUGOUT2("LINKS changed from %08X to %08X\n",
			  links_orig, links_reg);
	}

	if (link_up_wait_to_complete) {
		for (i = 0; i < hw->mac.max_link_up_time; i++) {
			if (links_reg & IXGBE_LINKS_UP) {
				*link_up = TRUE;
				break;
			} else {
				*link_up = FALSE;
			}
			msec_delay(100);
			links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
		}
	} else {
		if (links_reg & IXGBE_LINKS_UP)
			*link_up = TRUE;
		else
			*link_up = FALSE;
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
		if (hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T_L)
			*speed = IXGBE_LINK_SPEED_10_FULL;
		break;
	default:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
	}

	return IXGBE_SUCCESS;
}