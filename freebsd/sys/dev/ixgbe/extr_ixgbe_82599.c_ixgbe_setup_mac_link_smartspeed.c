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
struct TYPE_2__ {int autoneg_advertised; void* smart_speed_active; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int IXGBE_AUTOC_KR_SUPP ; 
 int IXGBE_AUTOC_KX4_KX_SUPP_MASK ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_LINK_SPEED_UNKNOWN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SMARTSPEED_MAX_RETRIES ; 
 scalar_t__ IXGBE_SUCCESS ; 
 void* TRUE ; 
 scalar_t__ ixgbe_check_link (struct ixgbe_hw*,int*,int*,void*) ; 
 scalar_t__ ixgbe_setup_mac_link_82599 (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 ixgbe_setup_mac_link_smartspeed(struct ixgbe_hw *hw,
				    ixgbe_link_speed speed,
				    bool autoneg_wait_to_complete)
{
	s32 status = IXGBE_SUCCESS;
	ixgbe_link_speed link_speed = IXGBE_LINK_SPEED_UNKNOWN;
	s32 i, j;
	bool link_up = FALSE;
	u32 autoc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);

	DEBUGFUNC("ixgbe_setup_mac_link_smartspeed");

	 /* Set autoneg_advertised value based on input link speed */
	hw->phy.autoneg_advertised = 0;

	if (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	if (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	if (speed & IXGBE_LINK_SPEED_100_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_100_FULL;

	/*
	 * Implement Intel SmartSpeed algorithm.  SmartSpeed will reduce the
	 * autoneg advertisement if link is unable to be established at the
	 * highest negotiated rate.  This can sometimes happen due to integrity
	 * issues with the physical media connection.
	 */

	/* First, try to get link with full advertisement */
	hw->phy.smart_speed_active = FALSE;
	for (j = 0; j < IXGBE_SMARTSPEED_MAX_RETRIES; j++) {
		status = ixgbe_setup_mac_link_82599(hw, speed,
						    autoneg_wait_to_complete);
		if (status != IXGBE_SUCCESS)
			goto out;

		/*
		 * Wait for the controller to acquire link.  Per IEEE 802.3ap,
		 * Section 73.10.2, we may have to wait up to 500ms if KR is
		 * attempted, or 200ms if KX/KX4/BX/BX4 is attempted, per
		 * Table 9 in the AN MAS.
		 */
		for (i = 0; i < 5; i++) {
			msec_delay(100);

			/* If we have link, just jump out */
			status = ixgbe_check_link(hw, &link_speed, &link_up,
						  FALSE);
			if (status != IXGBE_SUCCESS)
				goto out;

			if (link_up)
				goto out;
		}
	}

	/*
	 * We didn't get link.  If we advertised KR plus one of KX4/KX
	 * (or BX4/BX), then disable KR and try again.
	 */
	if (((autoc_reg & IXGBE_AUTOC_KR_SUPP) == 0) ||
	    ((autoc_reg & IXGBE_AUTOC_KX4_KX_SUPP_MASK) == 0))
		goto out;

	/* Turn SmartSpeed on to disable KR support */
	hw->phy.smart_speed_active = TRUE;
	status = ixgbe_setup_mac_link_82599(hw, speed,
					    autoneg_wait_to_complete);
	if (status != IXGBE_SUCCESS)
		goto out;

	/*
	 * Wait for the controller to acquire link.  600ms will allow for
	 * the AN link_fail_inhibit_timer as well for multiple cycles of
	 * parallel detect, both 10g and 1g. This allows for the maximum
	 * connect attempts as defined in the AN MAS table 73-7.
	 */
	for (i = 0; i < 6; i++) {
		msec_delay(100);

		/* If we have link, just jump out */
		status = ixgbe_check_link(hw, &link_speed, &link_up, FALSE);
		if (status != IXGBE_SUCCESS)
			goto out;

		if (link_up)
			goto out;
	}

	/* We didn't get link.  Turn SmartSpeed back off. */
	hw->phy.smart_speed_active = FALSE;
	status = ixgbe_setup_mac_link_82599(hw, speed,
					    autoneg_wait_to_complete);

out:
	if (link_up && (link_speed == IXGBE_LINK_SPEED_1GB_FULL))
		DEBUGOUT("Smartspeed has downgraded the link speed "
		"from the maximum advertised\n");
	return status;
}