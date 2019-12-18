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
struct TYPE_3__ {int phy_type; int an_info; } ;
struct TYPE_4__ {TYPE_1__ link_info; } ;
struct i40e_hw {TYPE_2__ phy; } ;
struct ixl_pf {int /*<<< orphan*/  link_up; struct i40e_hw hw; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int I40E_AQ_LINK_PAUSE_RX ; 
 int I40E_AQ_LINK_PAUSE_TX ; 
#define  I40E_PHY_TYPE_1000BASE_KX 161 
#define  I40E_PHY_TYPE_1000BASE_LX 160 
#define  I40E_PHY_TYPE_1000BASE_SX 159 
#define  I40E_PHY_TYPE_1000BASE_T 158 
#define  I40E_PHY_TYPE_1000BASE_T_OPTICAL 157 
#define  I40E_PHY_TYPE_100BASE_TX 156 
#define  I40E_PHY_TYPE_10GBASE_AOC 155 
#define  I40E_PHY_TYPE_10GBASE_CR1 154 
#define  I40E_PHY_TYPE_10GBASE_CR1_CU 153 
#define  I40E_PHY_TYPE_10GBASE_KR 152 
#define  I40E_PHY_TYPE_10GBASE_KX4 151 
#define  I40E_PHY_TYPE_10GBASE_LR 150 
#define  I40E_PHY_TYPE_10GBASE_SFPP_CU 149 
#define  I40E_PHY_TYPE_10GBASE_SR 148 
#define  I40E_PHY_TYPE_10GBASE_T 147 
#define  I40E_PHY_TYPE_20GBASE_KR2 146 
#define  I40E_PHY_TYPE_25GBASE_ACC 145 
#define  I40E_PHY_TYPE_25GBASE_AOC 144 
#define  I40E_PHY_TYPE_25GBASE_CR 143 
#define  I40E_PHY_TYPE_25GBASE_KR 142 
#define  I40E_PHY_TYPE_25GBASE_LR 141 
#define  I40E_PHY_TYPE_25GBASE_SR 140 
#define  I40E_PHY_TYPE_40GBASE_AOC 139 
#define  I40E_PHY_TYPE_40GBASE_CR4 138 
#define  I40E_PHY_TYPE_40GBASE_CR4_CU 137 
#define  I40E_PHY_TYPE_40GBASE_KR4 136 
#define  I40E_PHY_TYPE_40GBASE_LR4 135 
#define  I40E_PHY_TYPE_40GBASE_SR4 134 
#define  I40E_PHY_TYPE_SFI 133 
#define  I40E_PHY_TYPE_SGMII 132 
#define  I40E_PHY_TYPE_XAUI 131 
#define  I40E_PHY_TYPE_XFI 130 
#define  I40E_PHY_TYPE_XLAUI 129 
#define  I40E_PHY_TYPE_XLPPI 128 
 int /*<<< orphan*/  IFM_1000_KX ; 
 int /*<<< orphan*/  IFM_1000_LX ; 
 int /*<<< orphan*/  IFM_1000_SGMII ; 
 int /*<<< orphan*/  IFM_1000_SX ; 
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_100_TX ; 
 int /*<<< orphan*/  IFM_10G_AOC ; 
 int /*<<< orphan*/  IFM_10G_CR1 ; 
 int /*<<< orphan*/  IFM_10G_KR ; 
 int /*<<< orphan*/  IFM_10G_KX4 ; 
 int /*<<< orphan*/  IFM_10G_LR ; 
 int /*<<< orphan*/  IFM_10G_SFI ; 
 int /*<<< orphan*/  IFM_10G_SR ; 
 int /*<<< orphan*/  IFM_10G_T ; 
 int /*<<< orphan*/  IFM_10G_TWINAX ; 
 int /*<<< orphan*/  IFM_20G_KR2 ; 
 int /*<<< orphan*/  IFM_25G_ACC ; 
 int /*<<< orphan*/  IFM_25G_AOC ; 
 int /*<<< orphan*/  IFM_25G_CR ; 
 int /*<<< orphan*/  IFM_25G_KR ; 
 int /*<<< orphan*/  IFM_25G_LR ; 
 int /*<<< orphan*/  IFM_25G_SR ; 
 int /*<<< orphan*/  IFM_40G_CR4 ; 
 int /*<<< orphan*/  IFM_40G_KR4 ; 
 int /*<<< orphan*/  IFM_40G_LR4 ; 
 int /*<<< orphan*/  IFM_40G_SR4 ; 
 int /*<<< orphan*/  IFM_40G_XLPPI ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_ETH_RXPAUSE ; 
 int /*<<< orphan*/  IFM_ETH_TXPAUSE ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_OTHER ; 
 int /*<<< orphan*/  IFM_UNKNOWN ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_if_media_status(if_ctx_t ctx, struct ifmediareq *ifmr)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct i40e_hw  *hw = &pf->hw;

	INIT_DEBUGOUT("ixl_media_status: begin");

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (!pf->link_up) {
		return;
	}

	ifmr->ifm_status |= IFM_ACTIVE;
	/* Hardware is always full-duplex */
	ifmr->ifm_active |= IFM_FDX;

	switch (hw->phy.link_info.phy_type) {
		/* 100 M */
		case I40E_PHY_TYPE_100BASE_TX:
			ifmr->ifm_active |= IFM_100_TX;
			break;
		/* 1 G */
		case I40E_PHY_TYPE_1000BASE_T:
			ifmr->ifm_active |= IFM_1000_T;
			break;
		case I40E_PHY_TYPE_1000BASE_SX:
			ifmr->ifm_active |= IFM_1000_SX;
			break;
		case I40E_PHY_TYPE_1000BASE_LX:
			ifmr->ifm_active |= IFM_1000_LX;
			break;
		case I40E_PHY_TYPE_1000BASE_T_OPTICAL:
			ifmr->ifm_active |= IFM_1000_T;
			break;
		/* 10 G */
		case I40E_PHY_TYPE_10GBASE_SFPP_CU:
			ifmr->ifm_active |= IFM_10G_TWINAX;
			break;
		case I40E_PHY_TYPE_10GBASE_SR:
			ifmr->ifm_active |= IFM_10G_SR;
			break;
		case I40E_PHY_TYPE_10GBASE_LR:
			ifmr->ifm_active |= IFM_10G_LR;
			break;
		case I40E_PHY_TYPE_10GBASE_T:
			ifmr->ifm_active |= IFM_10G_T;
			break;
		case I40E_PHY_TYPE_XAUI:
		case I40E_PHY_TYPE_XFI:
			ifmr->ifm_active |= IFM_10G_TWINAX;
			break;
		case I40E_PHY_TYPE_10GBASE_AOC:
			ifmr->ifm_active |= IFM_10G_AOC;
			break;
		/* 25 G */
		case I40E_PHY_TYPE_25GBASE_KR:
			ifmr->ifm_active |= IFM_25G_KR;
			break;
		case I40E_PHY_TYPE_25GBASE_CR:
			ifmr->ifm_active |= IFM_25G_CR;
			break;
		case I40E_PHY_TYPE_25GBASE_SR:
			ifmr->ifm_active |= IFM_25G_SR;
			break;
		case I40E_PHY_TYPE_25GBASE_LR:
			ifmr->ifm_active |= IFM_25G_LR;
			break;
		case I40E_PHY_TYPE_25GBASE_AOC:
			ifmr->ifm_active |= IFM_25G_AOC;
			break;
		case I40E_PHY_TYPE_25GBASE_ACC:
			ifmr->ifm_active |= IFM_25G_ACC;
			break;
		/* 40 G */
		case I40E_PHY_TYPE_40GBASE_CR4:
		case I40E_PHY_TYPE_40GBASE_CR4_CU:
			ifmr->ifm_active |= IFM_40G_CR4;
			break;
		case I40E_PHY_TYPE_40GBASE_SR4:
			ifmr->ifm_active |= IFM_40G_SR4;
			break;
		case I40E_PHY_TYPE_40GBASE_LR4:
			ifmr->ifm_active |= IFM_40G_LR4;
			break;
		case I40E_PHY_TYPE_XLAUI:
			ifmr->ifm_active |= IFM_OTHER;
			break;
		case I40E_PHY_TYPE_1000BASE_KX:
			ifmr->ifm_active |= IFM_1000_KX;
			break;
		case I40E_PHY_TYPE_SGMII:
			ifmr->ifm_active |= IFM_1000_SGMII;
			break;
		/* ERJ: What's the difference between these? */
		case I40E_PHY_TYPE_10GBASE_CR1_CU:
		case I40E_PHY_TYPE_10GBASE_CR1:
			ifmr->ifm_active |= IFM_10G_CR1;
			break;
		case I40E_PHY_TYPE_10GBASE_KX4:
			ifmr->ifm_active |= IFM_10G_KX4;
			break;
		case I40E_PHY_TYPE_10GBASE_KR:
			ifmr->ifm_active |= IFM_10G_KR;
			break;
		case I40E_PHY_TYPE_SFI:
			ifmr->ifm_active |= IFM_10G_SFI;
			break;
		/* Our single 20G media type */
		case I40E_PHY_TYPE_20GBASE_KR2:
			ifmr->ifm_active |= IFM_20G_KR2;
			break;
		case I40E_PHY_TYPE_40GBASE_KR4:
			ifmr->ifm_active |= IFM_40G_KR4;
			break;
		case I40E_PHY_TYPE_XLPPI:
		case I40E_PHY_TYPE_40GBASE_AOC:
			ifmr->ifm_active |= IFM_40G_XLPPI;
			break;
		/* Unknown to driver */
		default:
			ifmr->ifm_active |= IFM_UNKNOWN;
			break;
	}
	/* Report flow control status as well */
	if (hw->phy.link_info.an_info & I40E_AQ_LINK_PAUSE_TX)
		ifmr->ifm_active |= IFM_ETH_TXPAUSE;
	if (hw->phy.link_info.an_info & I40E_AQ_LINK_PAUSE_RX)
		ifmr->ifm_active |= IFM_ETH_RXPAUSE;
}