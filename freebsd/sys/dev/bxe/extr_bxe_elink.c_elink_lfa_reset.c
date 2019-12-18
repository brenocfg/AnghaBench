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
struct elink_vars {scalar_t__ phy_flags; scalar_t__ link_up; } ;
struct elink_params {int port; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  lfa_base; int /*<<< orphan*/  link_flags; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_PHY_INITIALIZED ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_link_reset (struct elink_params*,struct elink_vars*,int) ; 
 int /*<<< orphan*/  elink_set_bmac_rx (struct bxe_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  elink_set_rx_filter (struct elink_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_set_umac_rxtx (struct elink_params*,int) ; 
 int /*<<< orphan*/  elink_set_xmac_rxtx (struct elink_params*,int) ; 

elink_status_t elink_lfa_reset(struct elink_params *params,
			       struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	vars->link_up = 0;
	vars->phy_flags = 0;
	params->link_flags &= ~ELINK_PHY_INITIALIZED;
	if (!params->lfa_base)
		return elink_link_reset(params, vars, 1);
	/*
	 * Activate NIG drain so that during this time the device won't send
	 * anything while it is unable to response.
	 */
	REG_WR(sc, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 1);

	/*
	 * Close gracefully the gate from BMAC to NIG such that no half packets
	 * are passed.
	 */
	if (!CHIP_IS_E3(sc))
		elink_set_bmac_rx(sc, params->chip_id, params->port, 0);

	if (CHIP_IS_E3(sc)) {
		elink_set_xmac_rxtx(params, 0);
		elink_set_umac_rxtx(params, 0);
	}
	/* Wait 10ms for the pipe to clean up*/
	DELAY(1000 * 10);

	/* Clean the NIG-BRB using the network filters in a way that will
	 * not cut a packet in the middle.
	 */
	elink_set_rx_filter(params, 0);

	/*
	 * Re-open the gate between the BMAC and the NIG, after verifying the
	 * gate to the BRB is closed, otherwise packets may arrive to the
	 * firmware before driver had initialized it. The target is to achieve
	 * minimum management protocol down time.
	 */
	if (!CHIP_IS_E3(sc))
		elink_set_bmac_rx(sc, params->chip_id, params->port, 1);

	if (CHIP_IS_E3(sc)) {
		elink_set_xmac_rxtx(params, 1);
		elink_set_umac_rxtx(params, 1);
	}
	/* Disable NIG drain */
	REG_WR(sc, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
	return ELINK_STATUS_OK;
}