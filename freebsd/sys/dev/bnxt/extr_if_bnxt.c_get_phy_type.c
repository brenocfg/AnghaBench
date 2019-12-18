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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct bnxt_link_info {scalar_t__ phy_type; int support_speeds; scalar_t__ media_type; } ;
struct bnxt_softc {struct bnxt_link_info link_info; } ;

/* Variables and functions */
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_MEDIA_TYPE_DAC ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_MEDIA_TYPE_FIBRE ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_MEDIA_TYPE_TP ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASECR ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKX ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASESR ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASET ; 
 scalar_t__ HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_UNKNOWN ; 
 int HWRM_PORT_PHY_QCFG_OUTPUT_SUPPORT_SPEEDS_20GB ; 
 int HWRM_PORT_PHY_QCFG_OUTPUT_SUPPORT_SPEEDS_2_5GB ; 

__attribute__((used)) static uint8_t
get_phy_type(struct bnxt_softc *softc)
{
	struct bnxt_link_info *link_info = &softc->link_info;
	uint8_t phy_type = link_info->phy_type;
	uint16_t supported;

	if (phy_type != HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_UNKNOWN)
		return phy_type;

	/* Deduce the phy type from the media type and supported speeds */
	supported = link_info->support_speeds;

	if (link_info->media_type ==
	    HWRM_PORT_PHY_QCFG_OUTPUT_MEDIA_TYPE_TP)
		return HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASET;
	if (link_info->media_type ==
	    HWRM_PORT_PHY_QCFG_OUTPUT_MEDIA_TYPE_DAC) {
		if (supported & HWRM_PORT_PHY_QCFG_OUTPUT_SUPPORT_SPEEDS_2_5GB)
			return HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKX;
		if (supported & HWRM_PORT_PHY_QCFG_OUTPUT_SUPPORT_SPEEDS_20GB)
			return HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASEKR;
		return HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASECR;
	}
	if (link_info->media_type ==
	    HWRM_PORT_PHY_QCFG_OUTPUT_MEDIA_TYPE_FIBRE)
		return HWRM_PORT_PHY_QCFG_OUTPUT_PHY_TYPE_BASESR;

	return phy_type;
}