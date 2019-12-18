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
typedef  int uint32_t ;
struct elink_vars {int flow_ctrl; int /*<<< orphan*/  mac_type; } ;
struct elink_params {int port; int feature_config_flags; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ELINK_FEATURE_CONFIG_PFC_ENABLED ; 
 int ELINK_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  ELINK_MAC_TYPE_BMAC ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_CLEAR ; 
 int MISC_REGISTERS_RESET_REG_2_RST_BMAC0 ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_SET ; 
 scalar_t__ NIG_REG_BMAC0_IN_EN ; 
 scalar_t__ NIG_REG_BMAC0_OUT_EN ; 
 scalar_t__ NIG_REG_BMAC0_PAUSE_OUT_EN ; 
 scalar_t__ NIG_REG_BMAC0_REGS_OUT_EN ; 
 scalar_t__ NIG_REG_EGRESS_EMAC0_OUT_EN ; 
 scalar_t__ NIG_REG_EGRESS_EMAC0_PORT ; 
 scalar_t__ NIG_REG_EMAC0_IN_EN ; 
 scalar_t__ NIG_REG_EMAC0_PAUSE_OUT_EN ; 
 scalar_t__ NIG_REG_XGXS_LANE_SEL_P0 ; 
 scalar_t__ NIG_REG_XGXS_SERDES0_MODE_SEL ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_bmac1_enable (struct elink_params*,struct elink_vars*,int) ; 
 int /*<<< orphan*/  elink_bmac2_enable (struct elink_params*,struct elink_vars*,int) ; 

__attribute__((used)) static elink_status_t elink_bmac_enable(struct elink_params *params,
			     struct elink_vars *vars,
			     uint8_t is_lb, uint8_t reset_bmac)
{
	elink_status_t rc = ELINK_STATUS_OK;
	uint8_t port = params->port;
	struct bxe_softc *sc = params->sc;
	uint32_t val;
	/* Reset and unreset the BigMac */
	if (reset_bmac) {
		REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
		       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));
		DELAY(1000 * 1);
	}

	REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));

	/* Enable access for bmac registers */
	REG_WR(sc, NIG_REG_BMAC0_REGS_OUT_EN + port*4, 0x1);

	/* Enable BMAC according to BMAC type*/
	if (CHIP_IS_E2(sc))
		rc = elink_bmac2_enable(params, vars, is_lb);
	else
		rc = elink_bmac1_enable(params, vars, is_lb);
	REG_WR(sc, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 0x1);
	REG_WR(sc, NIG_REG_XGXS_LANE_SEL_P0 + port*4, 0x0);
	REG_WR(sc, NIG_REG_EGRESS_EMAC0_PORT + port*4, 0x0);
	val = 0;
	if ((params->feature_config_flags &
	      ELINK_FEATURE_CONFIG_PFC_ENABLED) ||
	    (vars->flow_ctrl & ELINK_FLOW_CTRL_TX))
		val = 1;
	REG_WR(sc, NIG_REG_BMAC0_PAUSE_OUT_EN + port*4, val);
	REG_WR(sc, NIG_REG_EGRESS_EMAC0_OUT_EN + port*4, 0x0);
	REG_WR(sc, NIG_REG_EMAC0_IN_EN + port*4, 0x0);
	REG_WR(sc, NIG_REG_EMAC0_PAUSE_OUT_EN + port*4, 0x0);
	REG_WR(sc, NIG_REG_BMAC0_IN_EN + port*4, 0x1);
	REG_WR(sc, NIG_REG_BMAC0_OUT_EN + port*4, 0x1);

	vars->mac_type = ELINK_MAC_TYPE_BMAC;
	return rc;
}