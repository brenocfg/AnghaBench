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
struct TYPE_4__ {int /*<<< orphan*/  (* check_link ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct TYPE_6__ {int media_type; } ;
struct ixgbe_hw {int /*<<< orphan*/  device_id; TYPE_2__ mac; TYPE_3__ phy; } ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int FALSE ; 
#define  IXGBE_DEV_ID_82599_T3_LOM 146 
#define  IXGBE_DEV_ID_X540T 145 
#define  IXGBE_DEV_ID_X540T1 144 
#define  IXGBE_DEV_ID_X540_BYPASS 143 
#define  IXGBE_DEV_ID_X550EM_A_10G_T 142 
#define  IXGBE_DEV_ID_X550EM_A_1G_T 141 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 140 
#define  IXGBE_DEV_ID_X550EM_A_QSFP 139 
#define  IXGBE_DEV_ID_X550EM_A_QSFP_N 138 
#define  IXGBE_DEV_ID_X550EM_A_SFP 137 
#define  IXGBE_DEV_ID_X550EM_A_SFP_N 136 
#define  IXGBE_DEV_ID_X550EM_X_10G_T 135 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_X_XFI ; 
#define  IXGBE_DEV_ID_X550T 134 
#define  IXGBE_DEV_ID_X550T1 133 
 int /*<<< orphan*/  IXGBE_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 int TRUE ; 
#define  ixgbe_media_type_backplane 132 
#define  ixgbe_media_type_copper 131 
#define  ixgbe_media_type_fiber 130 
#define  ixgbe_media_type_fiber_fixed 129 
#define  ixgbe_media_type_fiber_qsfp 128 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ; 

bool ixgbe_device_supports_autoneg_fc(struct ixgbe_hw *hw)
{
	bool supported = FALSE;
	ixgbe_link_speed speed;
	bool link_up;

	DEBUGFUNC("ixgbe_device_supports_autoneg_fc");

	switch (hw->phy.media_type) {
	case ixgbe_media_type_fiber_fixed:
	case ixgbe_media_type_fiber_qsfp:
	case ixgbe_media_type_fiber:
		/* flow control autoneg black list */
		switch (hw->device_id) {
		case IXGBE_DEV_ID_X550EM_A_SFP:
		case IXGBE_DEV_ID_X550EM_A_SFP_N:
		case IXGBE_DEV_ID_X550EM_A_QSFP:
		case IXGBE_DEV_ID_X550EM_A_QSFP_N:
			supported = FALSE;
			break;
		default:
			hw->mac.ops.check_link(hw, &speed, &link_up, FALSE);
			/* if link is down, assume supported */
			if (link_up)
				supported = speed == IXGBE_LINK_SPEED_1GB_FULL ?
				TRUE : FALSE;
			else
				supported = TRUE;
		}

		break;
	case ixgbe_media_type_backplane:
		if (hw->device_id == IXGBE_DEV_ID_X550EM_X_XFI)
			supported = FALSE;
		else
			supported = TRUE;
		break;
	case ixgbe_media_type_copper:
		/* only some copper devices support flow control autoneg */
		switch (hw->device_id) {
		case IXGBE_DEV_ID_82599_T3_LOM:
		case IXGBE_DEV_ID_X540T:
		case IXGBE_DEV_ID_X540T1:
		case IXGBE_DEV_ID_X540_BYPASS:
		case IXGBE_DEV_ID_X550T:
		case IXGBE_DEV_ID_X550T1:
		case IXGBE_DEV_ID_X550EM_X_10G_T:
		case IXGBE_DEV_ID_X550EM_A_10G_T:
		case IXGBE_DEV_ID_X550EM_A_1G_T:
		case IXGBE_DEV_ID_X550EM_A_1G_T_L:
			supported = TRUE;
			break;
		default:
			supported = FALSE;
		}
	default:
		break;
	}

	if (!supported)
		ERROR_REPORT2(IXGBE_ERROR_UNSUPPORTED,
			      "Device %x does not support flow control autoneg",
			      hw->device_id);

	return supported;
}