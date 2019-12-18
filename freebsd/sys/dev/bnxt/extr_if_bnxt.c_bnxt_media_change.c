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
struct ifmediareq {int dummy; } ;
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct TYPE_2__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  req_link_speed; } ;
struct bnxt_softc {int /*<<< orphan*/  ctx; TYPE_1__ link_info; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_AUTONEG_SPEED ; 
 int EINVAL ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_100GB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_100MB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_10GB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_1GB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_20GB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_25GB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_2_5GB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_40GB ; 
 int /*<<< orphan*/  HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_50GB ; 
#define  IFM_1000_KX 153 
#define  IFM_1000_SGMII 152 
#define  IFM_1000_T 151 
#define  IFM_100G_CR4 150 
#define  IFM_100G_KR4 149 
#define  IFM_100G_LR4 148 
#define  IFM_100G_SR4 147 
#define  IFM_100_T 146 
#define  IFM_10G_CR1 145 
#define  IFM_10G_KR 144 
#define  IFM_10G_LR 143 
#define  IFM_10G_SR 142 
#define  IFM_10G_T 141 
#define  IFM_20G_KR2 140 
#define  IFM_2500_KX 139 
#define  IFM_2500_T 138 
#define  IFM_25G_CR 137 
#define  IFM_25G_KR 136 
#define  IFM_25G_SR 135 
#define  IFM_40G_CR4 134 
#define  IFM_40G_KR4 133 
#define  IFM_40G_LR4 132 
#define  IFM_40G_SR4 131 
#define  IFM_50G_CR2 130 
#define  IFM_50G_KR2 129 
#define  IFM_AUTO 128 
 scalar_t__ IFM_ETHER ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 int bnxt_hwrm_set_link_setting (struct bnxt_softc*,int,int,int) ; 
 int /*<<< orphan*/  bnxt_media_status (int /*<<< orphan*/ ,struct ifmediareq*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ifmedia* iflib_get_media (int /*<<< orphan*/ ) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_media_change(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	struct ifmedia *ifm = iflib_get_media(ctx);
	struct ifmediareq ifmr;
	int rc;

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER)
		return EINVAL;

	switch (IFM_SUBTYPE(ifm->ifm_media)) {
	case IFM_100_T:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_100MB;
		break;
	case IFM_1000_KX:
	case IFM_1000_T:
	case IFM_1000_SGMII:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_1GB;
		break;
	case IFM_2500_KX:
	case IFM_2500_T:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_2_5GB;
		break;
	case IFM_10G_CR1:
	case IFM_10G_KR:
	case IFM_10G_LR:
	case IFM_10G_SR:
	case IFM_10G_T:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_10GB;
		break;
	case IFM_20G_KR2:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_20GB;
		break;
	case IFM_25G_CR:
	case IFM_25G_KR:
	case IFM_25G_SR:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_25GB;
		break;
	case IFM_40G_CR4:
	case IFM_40G_KR4:
	case IFM_40G_LR4:
	case IFM_40G_SR4:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_40GB;
		break;
	case IFM_50G_CR2:
	case IFM_50G_KR2:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
		    HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_50GB;
		break;
	case IFM_100G_CR4:
	case IFM_100G_KR4:
	case IFM_100G_LR4:
	case IFM_100G_SR4:
		softc->link_info.autoneg &= ~BNXT_AUTONEG_SPEED;
		softc->link_info.req_link_speed =
			HWRM_PORT_PHY_CFG_INPUT_FORCE_LINK_SPEED_100GB;
		break;
	default:
		device_printf(softc->dev,
		    "Unsupported media type!  Using auto\n");
		/* Fall-through */
	case IFM_AUTO:
		// Auto
		softc->link_info.autoneg |= BNXT_AUTONEG_SPEED;
		break;
	}
	rc = bnxt_hwrm_set_link_setting(softc, true, true, true);
	bnxt_media_status(softc->ctx, &ifmr);
	return rc;
}