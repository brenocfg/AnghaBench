#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vm_pool; int flow_type; int flex_bytes; int* inner_mac; int tni_vni; int tunnel_type; int* src_ip; int* dst_ip; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_port; scalar_t__ bkt_hash; } ;
union ixgbe_atr_input {TYPE_2__ formatted; } ;
typedef  int u32 ;
struct TYPE_3__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
#define  IXGBE_ATR_L4TYPE_MASK 131 
 int /*<<< orphan*/  IXGBE_ERR_CONFIG ; 
 int /*<<< orphan*/  IXGBE_FDIRDIP4M ; 
 int /*<<< orphan*/  IXGBE_FDIRIP6M ; 
 int IXGBE_FDIRIP6M_ALWAYS_MASK ; 
 int IXGBE_FDIRIP6M_DIPM_SHIFT ; 
 int IXGBE_FDIRIP6M_INNER_MAC ; 
 int IXGBE_FDIRIP6M_TNI_VNI ; 
 int IXGBE_FDIRIP6M_TNI_VNI_24 ; 
 int IXGBE_FDIRIP6M_TUNNEL_TYPE ; 
 int /*<<< orphan*/  IXGBE_FDIRM ; 
 int IXGBE_FDIRM_DIPv6 ; 
 int IXGBE_FDIRM_FLEX ; 
 int IXGBE_FDIRM_L3P ; 
 int IXGBE_FDIRM_L4P ; 
 int IXGBE_FDIRM_POOL ; 
 int IXGBE_FDIRM_VLANID ; 
 int IXGBE_FDIRM_VLANP ; 
 int /*<<< orphan*/  IXGBE_FDIRSCTPM ; 
 int /*<<< orphan*/  IXGBE_FDIRSIP4M ; 
 int /*<<< orphan*/  IXGBE_FDIRTCPM ; 
 int /*<<< orphan*/  IXGBE_FDIRUDPM ; 
 int IXGBE_NTOHS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_BE32 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int) ; 
 int ixgbe_get_fdirtcpm_82599 (union ixgbe_atr_input*) ; 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

s32 ixgbe_fdir_set_input_mask_82599(struct ixgbe_hw *hw,
				    union ixgbe_atr_input *input_mask, bool cloud_mode)
{
	/* mask IPv6 since it is currently not supported */
	u32 fdirm = IXGBE_FDIRM_DIPv6;
	u32 fdirtcpm;
	u32 fdirip6m;
	UNREFERENCED_1PARAMETER(cloud_mode);
	DEBUGFUNC("ixgbe_fdir_set_atr_input_mask_82599");

	/*
	 * Program the relevant mask registers.  If src/dst_port or src/dst_addr
	 * are zero, then assume a full mask for that field.  Also assume that
	 * a VLAN of 0 is unspecified, so mask that out as well.  L4type
	 * cannot be masked out in this implementation.
	 *
	 * This also assumes IPv4 only.  IPv6 masking isn't supported at this
	 * point in time.
	 */

	/* verify bucket hash is cleared on hash generation */
	if (input_mask->formatted.bkt_hash)
		DEBUGOUT(" bucket hash should always be 0 in mask\n");

	/* Program FDIRM and verify partial masks */
	switch (input_mask->formatted.vm_pool & 0x7F) {
	case 0x0:
		fdirm |= IXGBE_FDIRM_POOL;
	case 0x7F:
		break;
	default:
		DEBUGOUT(" Error on vm pool mask\n");
		return IXGBE_ERR_CONFIG;
	}

	switch (input_mask->formatted.flow_type & IXGBE_ATR_L4TYPE_MASK) {
	case 0x0:
		fdirm |= IXGBE_FDIRM_L4P;
		if (input_mask->formatted.dst_port ||
		    input_mask->formatted.src_port) {
			DEBUGOUT(" Error on src/dst port mask\n");
			return IXGBE_ERR_CONFIG;
		}
	case IXGBE_ATR_L4TYPE_MASK:
		break;
	default:
		DEBUGOUT(" Error on flow type mask\n");
		return IXGBE_ERR_CONFIG;
	}

	switch (IXGBE_NTOHS(input_mask->formatted.vlan_id) & 0xEFFF) {
	case 0x0000:
		/* mask VLAN ID */
		fdirm |= IXGBE_FDIRM_VLANID;
		/* FALLTHROUGH */
	case 0x0FFF:
		/* mask VLAN priority */
		fdirm |= IXGBE_FDIRM_VLANP;
		break;
	case 0xE000:
		/* mask VLAN ID only */
		fdirm |= IXGBE_FDIRM_VLANID;
		/* fall through */
	case 0xEFFF:
		/* no VLAN fields masked */
		break;
	default:
		DEBUGOUT(" Error on VLAN mask\n");
		return IXGBE_ERR_CONFIG;
	}

	switch (input_mask->formatted.flex_bytes & 0xFFFF) {
	case 0x0000:
		/* Mask Flex Bytes */
		fdirm |= IXGBE_FDIRM_FLEX;
		/* fall through */
	case 0xFFFF:
		break;
	default:
		DEBUGOUT(" Error on flexible byte mask\n");
		return IXGBE_ERR_CONFIG;
	}

	if (cloud_mode) {
		fdirm |= IXGBE_FDIRM_L3P;
		fdirip6m = ((u32) 0xFFFFU << IXGBE_FDIRIP6M_DIPM_SHIFT);
		fdirip6m |= IXGBE_FDIRIP6M_ALWAYS_MASK;

		switch (input_mask->formatted.inner_mac[0] & 0xFF) {
		case 0x00:
			/* Mask inner MAC, fall through */
			fdirip6m |= IXGBE_FDIRIP6M_INNER_MAC;
		case 0xFF:
			break;
		default:
			DEBUGOUT(" Error on inner_mac byte mask\n");
			return IXGBE_ERR_CONFIG;
		}

		switch (input_mask->formatted.tni_vni & 0xFFFFFFFF) {
		case 0x0:
			/* Mask vxlan id */
			fdirip6m |= IXGBE_FDIRIP6M_TNI_VNI;
			break;
		case 0x00FFFFFF:
			fdirip6m |= IXGBE_FDIRIP6M_TNI_VNI_24;
			break;
		case 0xFFFFFFFF:
			break;
		default:
			DEBUGOUT(" Error on TNI/VNI byte mask\n");
			return IXGBE_ERR_CONFIG;
		}

		switch (input_mask->formatted.tunnel_type & 0xFFFF) {
		case 0x0:
			/* Mask turnnel type, fall through */
			fdirip6m |= IXGBE_FDIRIP6M_TUNNEL_TYPE;
		case 0xFFFF:
			break;
		default:
			DEBUGOUT(" Error on tunnel type byte mask\n");
			return IXGBE_ERR_CONFIG;
		}
		IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRIP6M, fdirip6m);

		/* Set all bits in FDIRTCPM, FDIRUDPM, FDIRSCTPM,
		 * FDIRSIP4M and FDIRDIP4M in cloud mode to allow
		 * L3/L3 packets to tunnel.
		 */
		IXGBE_WRITE_REG(hw, IXGBE_FDIRTCPM, 0xFFFFFFFF);
		IXGBE_WRITE_REG(hw, IXGBE_FDIRUDPM, 0xFFFFFFFF);
		IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRDIP4M, 0xFFFFFFFF);
		IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRSIP4M, 0xFFFFFFFF);
		switch (hw->mac.type) {
		case ixgbe_mac_X550:
		case ixgbe_mac_X550EM_x:
		case ixgbe_mac_X550EM_a:
			IXGBE_WRITE_REG(hw, IXGBE_FDIRSCTPM, 0xFFFFFFFF);
			break;
		default:
			break;
		}
	}

	/* Now mask VM pool and destination IPv6 - bits 5 and 2 */
	IXGBE_WRITE_REG(hw, IXGBE_FDIRM, fdirm);

	if (!cloud_mode) {
		/* store the TCP/UDP port masks, bit reversed from port
		 * layout */
		fdirtcpm = ixgbe_get_fdirtcpm_82599(input_mask);

		/* write both the same so that UDP and TCP use the same mask */
		IXGBE_WRITE_REG(hw, IXGBE_FDIRTCPM, ~fdirtcpm);
		IXGBE_WRITE_REG(hw, IXGBE_FDIRUDPM, ~fdirtcpm);
		/* also use it for SCTP */
		switch (hw->mac.type) {
		case ixgbe_mac_X550:
		case ixgbe_mac_X550EM_x:
		case ixgbe_mac_X550EM_a:
			IXGBE_WRITE_REG(hw, IXGBE_FDIRSCTPM, ~fdirtcpm);
			break;
		default:
			break;
		}

		/* store source and destination IP masks (big-enian) */
		IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRSIP4M,
				     ~input_mask->formatted.src_ip[0]);
		IXGBE_WRITE_REG_BE32(hw, IXGBE_FDIRDIP4M,
				     ~input_mask->formatted.dst_ip[0]);
	}
	return IXGBE_SUCCESS;
}