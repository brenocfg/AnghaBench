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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_dcb_config {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IXGBE_DCB_TX_CONFIG ; 
 int /*<<< orphan*/  IXGBE_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_desc_arbiter_82598 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_desc_arbiter_82599 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_unpack_bwgid_cee (struct ixgbe_dcb_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_unpack_max_cee (struct ixgbe_dcb_config*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_unpack_refill_cee (struct ixgbe_dcb_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_unpack_tsa_cee (struct ixgbe_dcb_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

s32 ixgbe_dcb_config_tx_desc_arbiter_cee(struct ixgbe_hw *hw,
				     struct ixgbe_dcb_config *dcb_config)
{
	s32 ret = IXGBE_NOT_IMPLEMENTED;
	u8 tsa[IXGBE_DCB_MAX_TRAFFIC_CLASS];
	u8 bwgid[IXGBE_DCB_MAX_TRAFFIC_CLASS];
	u16 refill[IXGBE_DCB_MAX_TRAFFIC_CLASS];
	u16 max[IXGBE_DCB_MAX_TRAFFIC_CLASS];

	ixgbe_dcb_unpack_refill_cee(dcb_config, IXGBE_DCB_TX_CONFIG, refill);
	ixgbe_dcb_unpack_max_cee(dcb_config, max);
	ixgbe_dcb_unpack_bwgid_cee(dcb_config, IXGBE_DCB_TX_CONFIG, bwgid);
	ixgbe_dcb_unpack_tsa_cee(dcb_config, IXGBE_DCB_TX_CONFIG, tsa);

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		ret = ixgbe_dcb_config_tx_desc_arbiter_82598(hw, refill, max,
							     bwgid, tsa);
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
#if !defined(NO_82599_SUPPORT) || !defined(NO_X540_SUPPORT)
		ret = ixgbe_dcb_config_tx_desc_arbiter_82599(hw, refill, max,
							     bwgid, tsa);
		break;
#endif
	default:
		break;
	}
	return ret;
}