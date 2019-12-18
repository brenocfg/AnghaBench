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
typedef  int uint8_t ;
struct elink_vars {int link_status; int phy_flags; int flow_ctrl; int eee_status; int /*<<< orphan*/  line_speed; scalar_t__ link_up; } ;
struct elink_params {int port; TYPE_1__* phy; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int ELINK_FLAGS_TX_ERROR_CHECK ; 
 int ELINK_FLOW_CTRL_RX ; 
 int ELINK_FLOW_CTRL_TX ; 
 int ELINK_INT_PHY ; 
 int /*<<< orphan*/  ELINK_LED_MODE_OPER ; 
 int ELINK_MAX_PHYS ; 
 scalar_t__ ELINK_SINGLE_MEDIA_DIRECT (struct elink_params*) ; 
 int /*<<< orphan*/  ELINK_SPEED_10000 ; 
 scalar_t__ ELINK_STATUS_NO_LINK ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_UP ; 
 int LINK_STATUS_PHYSICAL_LINK_FLAG ; 
 int LINK_STATUS_RX_FLOW_CONTROL_ENABLED ; 
 int LINK_STATUS_TX_FLOW_CONTROL_ENABLED ; 
 scalar_t__ MISC_REG_CPMU_LP_DR_ENABLE ; 
 scalar_t__ MISC_REG_CPMU_LP_FW_ENABLE_P0 ; 
 scalar_t__ MISC_REG_CPMU_LP_MASK_ENT_P0 ; 
 scalar_t__ NIG_REG_EGRESS_DRAIN0_MODE ; 
 int PHY_HALF_OPEN_CONN_FLAG ; 
 int PHY_PHYSICAL_LINK_FLAG ; 
 int PHY_SGMII_FLAG ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int SHMEM_EEE_ACTIVE_BIT ; 
 int SHMEM_EEE_LPI_REQUESTED_BIT ; 
 scalar_t__ USES_WARPCORE (struct bxe_softc*) ; 
 scalar_t__ elink_bmac_enable (struct elink_params*,struct elink_vars*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_check_half_open_conn (struct elink_params*,struct elink_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_emac_enable (struct elink_params*,struct elink_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_emac_program (struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_pbf_update (struct elink_params*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_set_gmii_tx_driver (struct elink_params*) ; 
 int /*<<< orphan*/  elink_set_led (struct elink_params*,struct elink_vars*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_umac_enable (struct elink_params*,struct elink_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_update_mng (struct elink_params*,int) ; 
 int /*<<< orphan*/  elink_update_mng_eee (struct elink_params*,int) ; 
 scalar_t__ elink_xmac_enable (struct elink_params*,struct elink_vars*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static elink_status_t elink_update_link_up(struct elink_params *params,
				struct elink_vars *vars,
				uint8_t link_10g)
{
	struct bxe_softc *sc = params->sc;
	uint8_t phy_idx, port = params->port;
	elink_status_t rc = ELINK_STATUS_OK;

	vars->link_status |= (LINK_STATUS_LINK_UP |
			      LINK_STATUS_PHYSICAL_LINK_FLAG);
	vars->phy_flags |= PHY_PHYSICAL_LINK_FLAG;

	if (vars->flow_ctrl & ELINK_FLOW_CTRL_TX)
		vars->link_status |=
			LINK_STATUS_TX_FLOW_CONTROL_ENABLED;

	if (vars->flow_ctrl & ELINK_FLOW_CTRL_RX)
		vars->link_status |=
			LINK_STATUS_RX_FLOW_CONTROL_ENABLED;
	if (USES_WARPCORE(sc)) {
		if (link_10g) {
			if (elink_xmac_enable(params, vars, 0) ==
			    ELINK_STATUS_NO_LINK) {
				ELINK_DEBUG_P0(sc, "Found errors on XMAC\n");
				vars->link_up = 0;
				vars->phy_flags |= PHY_HALF_OPEN_CONN_FLAG;
				vars->link_status &= ~LINK_STATUS_LINK_UP;
			}
		} else
			elink_umac_enable(params, vars, 0);
		elink_set_led(params, vars,
			      ELINK_LED_MODE_OPER, vars->line_speed);

		if ((vars->eee_status & SHMEM_EEE_ACTIVE_BIT) &&
		    (vars->eee_status & SHMEM_EEE_LPI_REQUESTED_BIT)) {
			ELINK_DEBUG_P0(sc, "Enabling LPI assertion\n");
			REG_WR(sc, MISC_REG_CPMU_LP_FW_ENABLE_P0 +
			       (params->port << 2), 1);
			REG_WR(sc, MISC_REG_CPMU_LP_DR_ENABLE, 1);
			REG_WR(sc, MISC_REG_CPMU_LP_MASK_ENT_P0 +
			       (params->port << 2), 0xfc20);
		}
	}
	if ((CHIP_IS_E1x(sc) ||
	     CHIP_IS_E2(sc))) {
		if (link_10g) {
			if (elink_bmac_enable(params, vars, 0, 1) ==
			    ELINK_STATUS_NO_LINK) {
				ELINK_DEBUG_P0(sc, "Found errors on BMAC\n");
				vars->link_up = 0;
				vars->phy_flags |= PHY_HALF_OPEN_CONN_FLAG;
				vars->link_status &= ~LINK_STATUS_LINK_UP;
			}

			elink_set_led(params, vars,
				      ELINK_LED_MODE_OPER, ELINK_SPEED_10000);
		} else {
			rc = elink_emac_program(params, vars);
			elink_emac_enable(params, vars, 0);

			/* AN complete? */
			if ((vars->link_status &
			     LINK_STATUS_AUTO_NEGOTIATE_COMPLETE)
			    && (!(vars->phy_flags & PHY_SGMII_FLAG)) &&
			    ELINK_SINGLE_MEDIA_DIRECT(params))
				elink_set_gmii_tx_driver(params);
		}
	}

	/* PBF - link up */
	if (CHIP_IS_E1x(sc))
		rc |= elink_pbf_update(params, vars->flow_ctrl,
				       vars->line_speed);

	/* Disable drain */
	REG_WR(sc, NIG_REG_EGRESS_DRAIN0_MODE + port*4, 0);

	/* Update shared memory */
	elink_update_mng(params, vars->link_status);
	elink_update_mng_eee(params, vars->eee_status);
	/* Check remote fault */
	for (phy_idx = ELINK_INT_PHY; phy_idx < ELINK_MAX_PHYS; phy_idx++) {
		if (params->phy[phy_idx].flags & ELINK_FLAGS_TX_ERROR_CHECK) {
			elink_check_half_open_conn(params, vars, 0);
			break;
		}
	}
	DELAY(1000 * 20);
	return rc;
}