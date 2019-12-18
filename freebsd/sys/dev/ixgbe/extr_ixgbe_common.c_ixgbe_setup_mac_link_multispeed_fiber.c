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
struct TYPE_2__ {int media_type; int autoneg_advertised; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int FALSE ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_LINK_SPEED_UNKNOWN ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_check_link (struct ixgbe_hw*,int*,int*,int) ; 
 int /*<<< orphan*/  ixgbe_flap_tx_laser (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_get_link_capabilities (struct ixgbe_hw*,int*,int*) ; 
#define  ixgbe_media_type_fiber 130 
#define  ixgbe_media_type_fiber_fixed 129 
#define  ixgbe_media_type_fiber_qsfp 128 
 int /*<<< orphan*/  ixgbe_set_rate_select_speed (struct ixgbe_hw*,int) ; 
 scalar_t__ ixgbe_setup_mac_link (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 ixgbe_setup_mac_link_multispeed_fiber(struct ixgbe_hw *hw,
					  ixgbe_link_speed speed,
					  bool autoneg_wait_to_complete)
{
	ixgbe_link_speed link_speed = IXGBE_LINK_SPEED_UNKNOWN;
	ixgbe_link_speed highest_link_speed = IXGBE_LINK_SPEED_UNKNOWN;
	s32 status = IXGBE_SUCCESS;
	u32 speedcnt = 0;
	u32 i = 0;
	bool autoneg, link_up = FALSE;

	DEBUGFUNC("ixgbe_setup_mac_link_multispeed_fiber");

	/* Mask off requested but non-supported speeds */
	status = ixgbe_get_link_capabilities(hw, &link_speed, &autoneg);
	if (status != IXGBE_SUCCESS)
		return status;

	speed &= link_speed;

	/* Try each speed one by one, highest priority first.  We do this in
	 * software because 10Gb fiber doesn't support speed autonegotiation.
	 */
	if (speed & IXGBE_LINK_SPEED_10GB_FULL) {
		speedcnt++;
		highest_link_speed = IXGBE_LINK_SPEED_10GB_FULL;

		/* Set the module link speed */
		switch (hw->phy.media_type) {
		case ixgbe_media_type_fiber_fixed:
		case ixgbe_media_type_fiber:
			ixgbe_set_rate_select_speed(hw,
						    IXGBE_LINK_SPEED_10GB_FULL);
			break;
		case ixgbe_media_type_fiber_qsfp:
			/* QSFP module automatically detects MAC link speed */
			break;
		default:
			DEBUGOUT("Unexpected media type.\n");
			break;
		}

		/* Allow module to change analog characteristics (1G->10G) */
		msec_delay(40);

		status = ixgbe_setup_mac_link(hw,
					      IXGBE_LINK_SPEED_10GB_FULL,
					      autoneg_wait_to_complete);
		if (status != IXGBE_SUCCESS)
			return status;

		/* Flap the Tx laser if it has not already been done */
		ixgbe_flap_tx_laser(hw);

		/* Wait for the controller to acquire link.  Per IEEE 802.3ap,
		 * Section 73.10.2, we may have to wait up to 500ms if KR is
		 * attempted.  82599 uses the same timing for 10g SFI.
		 */
		for (i = 0; i < 5; i++) {
			/* Wait for the link partner to also set speed */
			msec_delay(100);

			/* If we have link, just jump out */
			status = ixgbe_check_link(hw, &link_speed,
						  &link_up, FALSE);
			if (status != IXGBE_SUCCESS)
				return status;

			if (link_up)
				goto out;
		}
	}

	if (speed & IXGBE_LINK_SPEED_1GB_FULL) {
		speedcnt++;
		if (highest_link_speed == IXGBE_LINK_SPEED_UNKNOWN)
			highest_link_speed = IXGBE_LINK_SPEED_1GB_FULL;

		/* Set the module link speed */
		switch (hw->phy.media_type) {
		case ixgbe_media_type_fiber_fixed:
		case ixgbe_media_type_fiber:
			ixgbe_set_rate_select_speed(hw,
						    IXGBE_LINK_SPEED_1GB_FULL);
			break;
		case ixgbe_media_type_fiber_qsfp:
			/* QSFP module automatically detects link speed */
			break;
		default:
			DEBUGOUT("Unexpected media type.\n");
			break;
		}

		/* Allow module to change analog characteristics (10G->1G) */
		msec_delay(40);

		status = ixgbe_setup_mac_link(hw,
					      IXGBE_LINK_SPEED_1GB_FULL,
					      autoneg_wait_to_complete);
		if (status != IXGBE_SUCCESS)
			return status;

		/* Flap the Tx laser if it has not already been done */
		ixgbe_flap_tx_laser(hw);

		/* Wait for the link partner to also set speed */
		msec_delay(100);

		/* If we have link, just jump out */
		status = ixgbe_check_link(hw, &link_speed, &link_up, FALSE);
		if (status != IXGBE_SUCCESS)
			return status;

		if (link_up)
			goto out;
	}

	/* We didn't get link.  Configure back to the highest speed we tried,
	 * (if there was more than one).  We call ourselves back with just the
	 * single highest speed that the user requested.
	 */
	if (speedcnt > 1)
		status = ixgbe_setup_mac_link_multispeed_fiber(hw,
						      highest_link_speed,
						      autoneg_wait_to_complete);

out:
	/* Set autoneg_advertised value based on input link speed */
	hw->phy.autoneg_advertised = 0;

	if (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	if (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	return status;
}