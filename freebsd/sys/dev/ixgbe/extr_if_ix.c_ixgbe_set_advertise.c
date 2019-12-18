#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* get_link_capabilities ) (struct ixgbe_hw*,int*,int*) ;int /*<<< orphan*/  (* setup_link ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ ops; int /*<<< orphan*/  autotry_restart; } ;
struct TYPE_4__ {scalar_t__ media_type; scalar_t__ multispeed_fiber; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
struct adapter {int advertise; struct ixgbe_hw hw; int /*<<< orphan*/  ctx; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int FALSE ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_10_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 scalar_t__ IXGBE_NOT_IMPLEMENTED ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_media_type_backplane ; 
 scalar_t__ ixgbe_media_type_copper ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgbe_set_advertise(struct adapter *adapter, int advertise)
{
	device_t         dev = iflib_get_dev(adapter->ctx);
	struct ixgbe_hw  *hw;
	ixgbe_link_speed speed = 0;
	ixgbe_link_speed link_caps = 0;
	s32              err = IXGBE_NOT_IMPLEMENTED;
	bool             negotiate = FALSE;

	/* Checks to validate new value */
	if (adapter->advertise == advertise) /* no change */
		return (0);

	hw = &adapter->hw;

	/* No speed changes for backplane media */
	if (hw->phy.media_type == ixgbe_media_type_backplane)
		return (ENODEV);

	if (!((hw->phy.media_type == ixgbe_media_type_copper) ||
	      (hw->phy.multispeed_fiber))) {
		device_printf(dev, "Advertised speed can only be set on copper or multispeed fiber media types.\n");
		return (EINVAL);
	}

	if (advertise < 0x1 || advertise > 0xF) {
		device_printf(dev, "Invalid advertised speed; valid modes are 0x1 through 0xF\n");
		return (EINVAL);
	}

	if (hw->mac.ops.get_link_capabilities) {
		err = hw->mac.ops.get_link_capabilities(hw, &link_caps,
		    &negotiate);
		if (err != IXGBE_SUCCESS) {
			device_printf(dev, "Unable to determine supported advertise speeds\n");
			return (ENODEV);
		}
	}

	/* Set new value and report new advertised mode */
	if (advertise & 0x1) {
		if (!(link_caps & IXGBE_LINK_SPEED_100_FULL)) {
			device_printf(dev, "Interface does not support 100Mb advertised speed\n");
			return (EINVAL);
		}
		speed |= IXGBE_LINK_SPEED_100_FULL;
	}
	if (advertise & 0x2) {
		if (!(link_caps & IXGBE_LINK_SPEED_1GB_FULL)) {
			device_printf(dev, "Interface does not support 1Gb advertised speed\n");
			return (EINVAL);
		}
		speed |= IXGBE_LINK_SPEED_1GB_FULL;
	}
	if (advertise & 0x4) {
		if (!(link_caps & IXGBE_LINK_SPEED_10GB_FULL)) {
			device_printf(dev, "Interface does not support 10Gb advertised speed\n");
			return (EINVAL);
		}
		speed |= IXGBE_LINK_SPEED_10GB_FULL;
	}
	if (advertise & 0x8) {
		if (!(link_caps & IXGBE_LINK_SPEED_10_FULL)) {
			device_printf(dev, "Interface does not support 10Mb advertised speed\n");
			return (EINVAL);
		}
		speed |= IXGBE_LINK_SPEED_10_FULL;
	}

	hw->mac.autotry_restart = TRUE;
	hw->mac.ops.setup_link(hw, speed, TRUE);
	adapter->advertise = advertise;

	return (0);
}