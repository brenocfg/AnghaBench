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
struct TYPE_2__ {int type; int /*<<< orphan*/  multispeed_fiber; } ;
struct ixgbe_hw {int device_id; TYPE_1__ phy; } ;
typedef  enum ixgbe_media_type { ____Placeholder_ixgbe_media_type } ixgbe_media_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  IXGBE_DEV_ID_82599EN_SFP 145 
#define  IXGBE_DEV_ID_82599_BACKPLANE_FCOE 144 
#define  IXGBE_DEV_ID_82599_BYPASS 143 
#define  IXGBE_DEV_ID_82599_COMBO_BACKPLANE 142 
#define  IXGBE_DEV_ID_82599_CX4 141 
#define  IXGBE_DEV_ID_82599_KR 140 
#define  IXGBE_DEV_ID_82599_KX4 139 
#define  IXGBE_DEV_ID_82599_KX4_MEZZ 138 
#define  IXGBE_DEV_ID_82599_QSFP_SF_QP 137 
#define  IXGBE_DEV_ID_82599_SFP 136 
#define  IXGBE_DEV_ID_82599_SFP_EM 135 
#define  IXGBE_DEV_ID_82599_SFP_FCOE 134 
#define  IXGBE_DEV_ID_82599_SFP_SF2 133 
#define  IXGBE_DEV_ID_82599_SFP_SF_QP 132 
#define  IXGBE_DEV_ID_82599_T3_LOM 131 
#define  IXGBE_DEV_ID_82599_XAUI_LOM 130 
 int /*<<< orphan*/  TRUE ; 
 int ixgbe_media_type_backplane ; 
 int ixgbe_media_type_copper ; 
 int ixgbe_media_type_cx4 ; 
 int ixgbe_media_type_fiber ; 
 int ixgbe_media_type_fiber_fixed ; 
 int ixgbe_media_type_fiber_qsfp ; 
 int ixgbe_media_type_unknown ; 
#define  ixgbe_phy_cu_unknown 129 
#define  ixgbe_phy_tn 128 

enum ixgbe_media_type ixgbe_get_media_type_82599(struct ixgbe_hw *hw)
{
	enum ixgbe_media_type media_type;

	DEBUGFUNC("ixgbe_get_media_type_82599");

	/* Detect if there is a copper PHY attached. */
	switch (hw->phy.type) {
	case ixgbe_phy_cu_unknown:
	case ixgbe_phy_tn:
		media_type = ixgbe_media_type_copper;
		goto out;
	default:
		break;
	}

	switch (hw->device_id) {
	case IXGBE_DEV_ID_82599_KX4:
	case IXGBE_DEV_ID_82599_KX4_MEZZ:
	case IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
	case IXGBE_DEV_ID_82599_KR:
	case IXGBE_DEV_ID_82599_BACKPLANE_FCOE:
	case IXGBE_DEV_ID_82599_XAUI_LOM:
		/* Default device ID is mezzanine card KX/KX4 */
		media_type = ixgbe_media_type_backplane;
		break;
	case IXGBE_DEV_ID_82599_SFP:
	case IXGBE_DEV_ID_82599_SFP_FCOE:
	case IXGBE_DEV_ID_82599_SFP_EM:
	case IXGBE_DEV_ID_82599_SFP_SF2:
	case IXGBE_DEV_ID_82599_SFP_SF_QP:
	case IXGBE_DEV_ID_82599EN_SFP:
		media_type = ixgbe_media_type_fiber;
		break;
	case IXGBE_DEV_ID_82599_CX4:
		media_type = ixgbe_media_type_cx4;
		break;
	case IXGBE_DEV_ID_82599_T3_LOM:
		media_type = ixgbe_media_type_copper;
		break;
	case IXGBE_DEV_ID_82599_QSFP_SF_QP:
		media_type = ixgbe_media_type_fiber_qsfp;
		break;
	case IXGBE_DEV_ID_82599_BYPASS:
		media_type = ixgbe_media_type_fiber_fixed;
		hw->phy.multispeed_fiber = TRUE;
		break;
	default:
		media_type = ixgbe_media_type_unknown;
		break;
	}
out:
	return media_type;
}