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
typedef  scalar_t__ uint8_t ;
struct elink_vars {int /*<<< orphan*/  link_status; } ;
struct elink_params {scalar_t__ multi_phy_config; scalar_t__ num_phys; scalar_t__* req_line_speed; TYPE_1__* phy; int /*<<< orphan*/ * req_duplex; int /*<<< orphan*/ * speed_cap_mask; int /*<<< orphan*/ * req_flow_ctrl; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ req_line_speed; int /*<<< orphan*/  speed_cap_mask; int /*<<< orphan*/  req_flow_ctrl; int /*<<< orphan*/  req_duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ELINK_EXT_PHY1 ; 
 scalar_t__ ELINK_EXT_PHY2 ; 
 scalar_t__ ELINK_INT_PHY ; 
 scalar_t__ ELINK_LINK_CONFIG_IDX (scalar_t__) ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  LINK_STATUS_AUTO_NEGOTIATE_ENABLED ; 
 scalar_t__ PORT_HW_CFG_PHY_SWAPPED_ENABLED ; 

__attribute__((used)) static void set_phy_vars(struct elink_params *params,
			 struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint8_t actual_phy_idx, phy_index, link_cfg_idx;
	uint8_t phy_config_swapped = params->multi_phy_config &
			PORT_HW_CFG_PHY_SWAPPED_ENABLED;
	for (phy_index = ELINK_INT_PHY; phy_index < params->num_phys;
	      phy_index++) {
		link_cfg_idx = ELINK_LINK_CONFIG_IDX(phy_index);
		actual_phy_idx = phy_index;
		if (phy_config_swapped) {
			if (phy_index == ELINK_EXT_PHY1)
				actual_phy_idx = ELINK_EXT_PHY2;
			else if (phy_index == ELINK_EXT_PHY2)
				actual_phy_idx = ELINK_EXT_PHY1;
		}
		params->phy[actual_phy_idx].req_flow_ctrl =
			params->req_flow_ctrl[link_cfg_idx];

		params->phy[actual_phy_idx].req_line_speed =
			params->req_line_speed[link_cfg_idx];

		params->phy[actual_phy_idx].speed_cap_mask =
			params->speed_cap_mask[link_cfg_idx];

		params->phy[actual_phy_idx].req_duplex =
			params->req_duplex[link_cfg_idx];

		if (params->req_line_speed[link_cfg_idx] ==
		    ELINK_SPEED_AUTO_NEG)
			vars->link_status |= LINK_STATUS_AUTO_NEGOTIATE_ENABLED;

		ELINK_DEBUG_P3(sc, "req_flow_ctrl %x, req_line_speed %x,"
			   " speed_cap_mask %x\n",
			   params->phy[actual_phy_idx].req_flow_ctrl,
			   params->phy[actual_phy_idx].req_line_speed,
			   params->phy[actual_phy_idx].speed_cap_mask);
	}
}