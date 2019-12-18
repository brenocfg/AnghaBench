#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elink_vars {int link_up; int /*<<< orphan*/  phy_flags; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  duplex; scalar_t__ line_speed; } ;
struct elink_params {int port; TYPE_1__* phy; scalar_t__* req_line_speed; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* config_loopback ) (TYPE_1__*,struct elink_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_FLOW_CTRL_NONE ; 
 size_t ELINK_INT_PHY ; 
 int /*<<< orphan*/  ELINK_MAC_TYPE_XMAC ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int /*<<< orphan*/  PHY_XGXS_FLAG ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_set_aer_mmd (struct elink_params*,TYPE_1__*) ; 
 int /*<<< orphan*/  elink_warpcore_reset_lane (struct bxe_softc*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_xmac_enable (struct elink_params*,struct elink_vars*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct elink_params*) ; 

__attribute__((used)) static void elink_init_xmac_loopback(struct elink_params *params,
				     struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	vars->link_up = 1;
	if (!params->req_line_speed[0])
		vars->line_speed = ELINK_SPEED_10000;
	else
		vars->line_speed = params->req_line_speed[0];
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = ELINK_FLOW_CTRL_NONE;
	vars->mac_type = ELINK_MAC_TYPE_XMAC;
	vars->phy_flags = PHY_XGXS_FLAG;
	/* Set WC to loopback mode since link is required to provide clock
	 * to the XMAC in 20G mode
	 */
	elink_set_aer_mmd(params, &params->phy[0]);
	elink_warpcore_reset_lane(sc, &params->phy[0], 0);
	params->phy[ELINK_INT_PHY].config_loopback(
			&params->phy[ELINK_INT_PHY],
			params);

	elink_xmac_enable(params, vars, 1);
	REG_WR(sc, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
}