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
typedef  int uint32_t ;
struct elink_vars {scalar_t__ line_speed; int eee_status; int flow_ctrl; int /*<<< orphan*/  mac_type; } ;
struct elink_params {int port; TYPE_1__* phy; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;
struct TYPE_2__ {int flags; int supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int ELINK_FLAGS_TX_ERROR_CHECK ; 
 int ELINK_FLOW_CTRL_TX ; 
 size_t ELINK_INT_PHY ; 
 int /*<<< orphan*/  ELINK_MAC_TYPE_XMAC ; 
 scalar_t__ ELINK_SPEED_20000 ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int ELINK_SUPPORTED_20000baseKR2_Full ; 
 int GRCBASE_XMAC0 ; 
 int GRCBASE_XMAC1 ; 
 int NIG_REG_EGRESS_EMAC0_PORT ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SHMEM_EEE_ADV_STATUS_MASK ; 
 int XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_LOCAL_FAULT_STATUS ; 
 int XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_REMOTE_FAULT_STATUS ; 
 int XMAC_CTRL_REG_LINE_LOCAL_LPBK ; 
 int XMAC_CTRL_REG_RX_EN ; 
 int XMAC_CTRL_REG_TX_EN ; 
 int XMAC_CTRL_REG_XLGMII_ALIGN_ENB ; 
 int XMAC_REG_CLEAR_RX_LSS_STATUS ; 
 int XMAC_REG_CTRL ; 
 int XMAC_REG_EEE_CTRL ; 
 int XMAC_REG_EEE_TIMERS_HI ; 
 int XMAC_REG_RX_LSS_CTRL ; 
 int XMAC_REG_RX_MAX_SIZE ; 
 int XMAC_REG_TX_CTRL ; 
 int XMAC_RX_LSS_CTRL_REG_LOCAL_FAULT_DISABLE ; 
 int XMAC_RX_LSS_CTRL_REG_REMOTE_FAULT_DISABLE ; 
 int /*<<< orphan*/  elink_set_xumac_nig (struct elink_params*,int,int) ; 
 int /*<<< orphan*/  elink_update_pfc_xmac (struct elink_params*,struct elink_vars*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_xmac_init (struct elink_params*,scalar_t__) ; 

__attribute__((used)) static elink_status_t elink_xmac_enable(struct elink_params *params,
			     struct elink_vars *vars, uint8_t lb)
{
	uint32_t val, xmac_base;
	struct bxe_softc *sc = params->sc;
	ELINK_DEBUG_P0(sc, "enabling XMAC\n");

	xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;

	elink_xmac_init(params, vars->line_speed);

	/* This register determines on which events the MAC will assert
	 * error on the i/f to the NIG along w/ EOP.
	 */

	/* This register tells the NIG whether to send traffic to UMAC
	 * or XMAC
	 */
	REG_WR(sc, NIG_REG_EGRESS_EMAC0_PORT + params->port*4, 0);

	/* When XMAC is in XLGMII mode, disable sending idles for fault
	 * detection.
	 */
	if (!(params->phy[ELINK_INT_PHY].flags & ELINK_FLAGS_TX_ERROR_CHECK)) {
		REG_WR(sc, xmac_base + XMAC_REG_RX_LSS_CTRL,
		       (XMAC_RX_LSS_CTRL_REG_LOCAL_FAULT_DISABLE |
			XMAC_RX_LSS_CTRL_REG_REMOTE_FAULT_DISABLE));
		REG_WR(sc, xmac_base + XMAC_REG_CLEAR_RX_LSS_STATUS, 0);
		REG_WR(sc, xmac_base + XMAC_REG_CLEAR_RX_LSS_STATUS,
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_LOCAL_FAULT_STATUS |
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_REMOTE_FAULT_STATUS);
	}
	/* Set Max packet size */
	REG_WR(sc, xmac_base + XMAC_REG_RX_MAX_SIZE, 0x2710);

	/* CRC append for Tx packets */
	REG_WR(sc, xmac_base + XMAC_REG_TX_CTRL, 0xC800);

	/* update PFC */
	elink_update_pfc_xmac(params, vars, 0);

	if (vars->eee_status & SHMEM_EEE_ADV_STATUS_MASK) {
		ELINK_DEBUG_P0(sc, "Setting XMAC for EEE\n");
		REG_WR(sc, xmac_base + XMAC_REG_EEE_TIMERS_HI, 0x1380008);
		REG_WR(sc, xmac_base + XMAC_REG_EEE_CTRL, 0x1);
	} else {
		REG_WR(sc, xmac_base + XMAC_REG_EEE_CTRL, 0x0);
	}

	/* Enable TX and RX */
	val = XMAC_CTRL_REG_TX_EN | XMAC_CTRL_REG_RX_EN;

	/* Set MAC in XLGMII mode for dual-mode */
	if ((vars->line_speed == ELINK_SPEED_20000) &&
	    (params->phy[ELINK_INT_PHY].supported &
	     ELINK_SUPPORTED_20000baseKR2_Full))
		val |= XMAC_CTRL_REG_XLGMII_ALIGN_ENB;

	/* Check loopback mode */
	if (lb)
		val |= XMAC_CTRL_REG_LINE_LOCAL_LPBK;
	REG_WR(sc, xmac_base + XMAC_REG_CTRL, val);
	elink_set_xumac_nig(params,
			    ((vars->flow_ctrl & ELINK_FLOW_CTRL_TX) != 0), 1);

	vars->mac_type = ELINK_MAC_TYPE_XMAC;

	return ELINK_STATUS_OK;
}