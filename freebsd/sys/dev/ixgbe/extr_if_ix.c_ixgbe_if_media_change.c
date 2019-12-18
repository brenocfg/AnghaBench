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
struct TYPE_5__ {int /*<<< orphan*/  (* setup_link ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ ops; int /*<<< orphan*/  autotry_restart; } ;
struct TYPE_4__ {scalar_t__ media_type; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct adapter {int advertise; struct ixgbe_hw hw; } ;
typedef  int ixgbe_link_speed ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  IFM_1000_CX 143 
#define  IFM_1000_KX 142 
#define  IFM_1000_LX 141 
#define  IFM_1000_SX 140 
#define  IFM_1000_T 139 
#define  IFM_100_TX 138 
#define  IFM_10G_CX4 137 
#define  IFM_10G_KR 136 
#define  IFM_10G_KX4 135 
#define  IFM_10G_LR 134 
#define  IFM_10G_LRM 133 
#define  IFM_10G_SR 132 
#define  IFM_10G_T 131 
#define  IFM_10G_TWINAX 130 
#define  IFM_10_T 129 
#define  IFM_AUTO 128 
 scalar_t__ IFM_ETHER ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_10_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ifmedia* iflib_get_media (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_media_type_backplane ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgbe_if_media_change(if_ctx_t ctx)
{
	struct adapter   *adapter = iflib_get_softc(ctx);
	struct ifmedia   *ifm = iflib_get_media(ctx);
	struct ixgbe_hw  *hw = &adapter->hw;
	ixgbe_link_speed speed = 0;

	INIT_DEBUGOUT("ixgbe_if_media_change: begin");

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER)
		return (EINVAL);

	if (hw->phy.media_type == ixgbe_media_type_backplane)
		return (EPERM);

	/*
	 * We don't actually need to check against the supported
	 * media types of the adapter; ifmedia will take care of
	 * that for us.
	 */
	switch (IFM_SUBTYPE(ifm->ifm_media)) {
	case IFM_AUTO:
	case IFM_10G_T:
		speed |= IXGBE_LINK_SPEED_100_FULL;
		speed |= IXGBE_LINK_SPEED_1GB_FULL;
		speed |= IXGBE_LINK_SPEED_10GB_FULL;
		break;
	case IFM_10G_LRM:
	case IFM_10G_LR:
#ifndef IFM_ETH_XTYPE
	case IFM_10G_SR: /* KR, too */
	case IFM_10G_CX4: /* KX4 */
#else
	case IFM_10G_KR:
	case IFM_10G_KX4:
#endif
		speed |= IXGBE_LINK_SPEED_1GB_FULL;
		speed |= IXGBE_LINK_SPEED_10GB_FULL;
		break;
#ifndef IFM_ETH_XTYPE
	case IFM_1000_CX: /* KX */
#else
	case IFM_1000_KX:
#endif
	case IFM_1000_LX:
	case IFM_1000_SX:
		speed |= IXGBE_LINK_SPEED_1GB_FULL;
		break;
	case IFM_1000_T:
		speed |= IXGBE_LINK_SPEED_100_FULL;
		speed |= IXGBE_LINK_SPEED_1GB_FULL;
		break;
	case IFM_10G_TWINAX:
		speed |= IXGBE_LINK_SPEED_10GB_FULL;
		break;
	case IFM_100_TX:
		speed |= IXGBE_LINK_SPEED_100_FULL;
		break;
	case IFM_10_T:
		speed |= IXGBE_LINK_SPEED_10_FULL;
		break;
	default:
		goto invalid;
	}

	hw->mac.autotry_restart = TRUE;
	hw->mac.ops.setup_link(hw, speed, TRUE);
	adapter->advertise =
	    ((speed & IXGBE_LINK_SPEED_10GB_FULL) ? 4 : 0) |
	    ((speed & IXGBE_LINK_SPEED_1GB_FULL)  ? 2 : 0) |
	    ((speed & IXGBE_LINK_SPEED_100_FULL)  ? 1 : 0) |
	    ((speed & IXGBE_LINK_SPEED_10_FULL)   ? 8 : 0);

	return (0);

invalid:
	device_printf(iflib_get_dev(ctx), "Invalid media type!\n");

	return (EINVAL);
}