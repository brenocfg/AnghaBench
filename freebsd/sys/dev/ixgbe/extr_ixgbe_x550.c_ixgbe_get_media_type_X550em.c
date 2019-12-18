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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {int device_id; TYPE_1__ phy; } ;
typedef  enum ixgbe_media_type { ____Placeholder_ixgbe_media_type } ixgbe_media_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  IXGBE_DEV_ID_X550EM_A_10G_T 144 
#define  IXGBE_DEV_ID_X550EM_A_1G_T 143 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 142 
#define  IXGBE_DEV_ID_X550EM_A_KR 141 
#define  IXGBE_DEV_ID_X550EM_A_KR_L 140 
#define  IXGBE_DEV_ID_X550EM_A_QSFP 139 
#define  IXGBE_DEV_ID_X550EM_A_QSFP_N 138 
#define  IXGBE_DEV_ID_X550EM_A_SFP 137 
#define  IXGBE_DEV_ID_X550EM_A_SFP_N 136 
#define  IXGBE_DEV_ID_X550EM_A_SGMII 135 
#define  IXGBE_DEV_ID_X550EM_A_SGMII_L 134 
#define  IXGBE_DEV_ID_X550EM_X_10G_T 133 
#define  IXGBE_DEV_ID_X550EM_X_1G_T 132 
#define  IXGBE_DEV_ID_X550EM_X_KR 131 
#define  IXGBE_DEV_ID_X550EM_X_KX4 130 
#define  IXGBE_DEV_ID_X550EM_X_SFP 129 
#define  IXGBE_DEV_ID_X550EM_X_XFI 128 
 int ixgbe_media_type_backplane ; 
 int ixgbe_media_type_copper ; 
 int ixgbe_media_type_fiber ; 
 int ixgbe_media_type_unknown ; 
 int /*<<< orphan*/  ixgbe_phy_sgmii ; 

enum ixgbe_media_type ixgbe_get_media_type_X550em(struct ixgbe_hw *hw)
{
	enum ixgbe_media_type media_type;

	DEBUGFUNC("ixgbe_get_media_type_X550em");

	/* Detect if there is a copper PHY attached. */
	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_X_KR:
	case IXGBE_DEV_ID_X550EM_X_KX4:
	case IXGBE_DEV_ID_X550EM_X_XFI:
	case IXGBE_DEV_ID_X550EM_A_KR:
	case IXGBE_DEV_ID_X550EM_A_KR_L:
		media_type = ixgbe_media_type_backplane;
		break;
	case IXGBE_DEV_ID_X550EM_X_SFP:
	case IXGBE_DEV_ID_X550EM_A_SFP:
	case IXGBE_DEV_ID_X550EM_A_SFP_N:
	case IXGBE_DEV_ID_X550EM_A_QSFP:
	case IXGBE_DEV_ID_X550EM_A_QSFP_N:
		media_type = ixgbe_media_type_fiber;
		break;
	case IXGBE_DEV_ID_X550EM_X_1G_T:
	case IXGBE_DEV_ID_X550EM_X_10G_T:
	case IXGBE_DEV_ID_X550EM_A_10G_T:
		media_type = ixgbe_media_type_copper;
		break;
	case IXGBE_DEV_ID_X550EM_A_SGMII:
	case IXGBE_DEV_ID_X550EM_A_SGMII_L:
		media_type = ixgbe_media_type_backplane;
		hw->phy.type = ixgbe_phy_sgmii;
		break;
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
		media_type = ixgbe_media_type_copper;
		break;
	default:
		media_type = ixgbe_media_type_unknown;
		break;
	}
	return media_type;
}