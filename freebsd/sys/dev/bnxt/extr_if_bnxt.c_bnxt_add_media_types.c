#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bnxt_link_info {int /*<<< orphan*/  support_speeds; } ;
struct bnxt_softc {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  media; struct bnxt_link_info link_info; } ;

/* Variables and functions */
 int BNXT_FLAG_NPAR ; 
 int /*<<< orphan*/  BNXT_IFMEDIA_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASECR4 155 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASEER4 154 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASELR4 153 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASESR10 152 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASESR4 151 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_1G_BASECX 150 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_1G_BASESX 149 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_1G_BASET 148 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASECR_CA_L 147 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASECR_CA_N 146 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASECR_CA_S 145 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASESR 144 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_ACTIVE_CABLE 143 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASECR4 142 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASEER4 141 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASELR4 140 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASESR4 139 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASECR 138 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR 137 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR2 136 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR4 135 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKX 134 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASELR 133 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASESR 132 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASET 131 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASETE 130 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_SGMIIEXTPHY 129 
#define  HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  IFM_1000_CX ; 
 int /*<<< orphan*/  IFM_1000_KX ; 
 int /*<<< orphan*/  IFM_1000_LX ; 
 int /*<<< orphan*/  IFM_1000_SGMII ; 
 int /*<<< orphan*/  IFM_1000_SX ; 
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_100G_CR4 ; 
 int /*<<< orphan*/  IFM_100G_KR4 ; 
 int /*<<< orphan*/  IFM_100G_LR4 ; 
 int /*<<< orphan*/  IFM_100G_SR4 ; 
 int /*<<< orphan*/  IFM_100_T ; 
 int /*<<< orphan*/  IFM_10G_AOC ; 
 int /*<<< orphan*/  IFM_10G_CR1 ; 
 int /*<<< orphan*/  IFM_10G_KR ; 
 int /*<<< orphan*/  IFM_10G_LR ; 
 int /*<<< orphan*/  IFM_10G_SR ; 
 int /*<<< orphan*/  IFM_10G_T ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_20G_KR2 ; 
 int /*<<< orphan*/  IFM_2500_KX ; 
 int /*<<< orphan*/  IFM_2500_T ; 
 int /*<<< orphan*/  IFM_25G_ACC ; 
 int /*<<< orphan*/  IFM_25G_CR ; 
 int /*<<< orphan*/  IFM_25G_KR ; 
 int /*<<< orphan*/  IFM_25G_LR ; 
 int /*<<< orphan*/  IFM_25G_SR ; 
 int /*<<< orphan*/  IFM_40G_CR4 ; 
 int /*<<< orphan*/  IFM_40G_KR4 ; 
 int /*<<< orphan*/  IFM_40G_LR4 ; 
 int /*<<< orphan*/  IFM_40G_SR4 ; 
 int /*<<< orphan*/  IFM_50G_CR2 ; 
 int /*<<< orphan*/  IFM_50G_KR2 ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  SPEEDS_100GB ; 
 int /*<<< orphan*/  SPEEDS_100MB ; 
 int /*<<< orphan*/  SPEEDS_10GB ; 
 int /*<<< orphan*/  SPEEDS_10MB ; 
 int /*<<< orphan*/  SPEEDS_1GB ; 
 int /*<<< orphan*/  SPEEDS_1GBHD ; 
 int /*<<< orphan*/  SPEEDS_20GB ; 
 int /*<<< orphan*/  SPEEDS_25GB ; 
 int /*<<< orphan*/  SPEEDS_2_5GB ; 
 int /*<<< orphan*/  SPEEDS_40GB ; 
 int /*<<< orphan*/  SPEEDS_50GB ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int get_phy_type (struct bnxt_softc*) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnxt_add_media_types(struct bnxt_softc *softc)
{
	struct bnxt_link_info *link_info = &softc->link_info;
	uint16_t supported;
	uint8_t phy_type = get_phy_type(softc);

	supported = link_info->support_speeds;

	/* Auto is always supported */
	ifmedia_add(softc->media, IFM_ETHER | IFM_AUTO, 0, NULL);

	if (softc->flags & BNXT_FLAG_NPAR)
		return;

	switch (phy_type) {
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASECR4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASECR4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASECR_CA_L:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASECR_CA_S:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASECR_CA_N:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASECR:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_100GB, IFM_100G_CR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_50GB, IFM_50G_CR2);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_40GB, IFM_40G_CR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_25GB, IFM_25G_CR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10GB, IFM_10G_CR1);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GB, IFM_1000_T);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASELR4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASELR4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASELR:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_100GB, IFM_100G_LR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_40GB, IFM_40G_LR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_25GB, IFM_25G_LR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10GB, IFM_10G_LR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GB, IFM_1000_LX);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASESR10:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASESR4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASESR4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASESR:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_BASEER4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_100G_BASEER4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_25G_BASESR:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_1G_BASESX:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_100GB, IFM_100G_SR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_40GB, IFM_40G_SR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_25GB, IFM_25G_SR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10GB, IFM_10G_SR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GB, IFM_1000_SX);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR4:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR2:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_100GB, IFM_100G_KR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_50GB, IFM_50G_KR2);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_40GB, IFM_40G_KR4);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_25GB, IFM_25G_KR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_20GB, IFM_20G_KR2);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10GB, IFM_10G_KR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GB, IFM_1000_KX);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_40G_ACTIVE_CABLE:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_25GB, IFM_25G_ACC);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10GB, IFM_10G_AOC);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_1G_BASECX:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GBHD, IFM_1000_CX);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_1G_BASET:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASET:
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASETE:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10GB, IFM_10G_T);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_2_5GB, IFM_2500_T);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GB, IFM_1000_T);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_100MB, IFM_100_T);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10MB, IFM_10_T);
		break;
	
	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKX:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_10GB, IFM_10G_KR);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_2_5GB, IFM_2500_KX);
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GB, IFM_1000_KX);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_SGMIIEXTPHY:
		BNXT_IFMEDIA_ADD(supported, SPEEDS_1GB, IFM_1000_SGMII);
		break;

	case HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_UNKNOWN:
		/* Only Autoneg is supported for TYPE_UNKNOWN */
		device_printf(softc->dev, "Unknown phy type\n");
		break;

        default:
		/* Only Autoneg is supported for new phy type values */
		device_printf(softc->dev, "phy type %d not supported by driver\n", phy_type);
		break;
	}

	return;
}