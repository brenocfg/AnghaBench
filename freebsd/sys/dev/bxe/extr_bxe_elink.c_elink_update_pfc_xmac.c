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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct elink_vars {int flow_ctrl; } ;
struct elink_params {int feature_config_flags; int* mac_addr; scalar_t__ port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ELINK_FEATURE_CONFIG_PFC_ENABLED ; 
 int ELINK_FLOW_CTRL_RX ; 
 int ELINK_FLOW_CTRL_TX ; 
 int GRCBASE_XMAC0 ; 
 int GRCBASE_XMAC1 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int XMAC_PAUSE_CTRL_REG_RX_PAUSE_EN ; 
 int XMAC_PAUSE_CTRL_REG_TX_PAUSE_EN ; 
 int XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON ; 
 int XMAC_PFC_CTRL_HI_REG_PFC_REFRESH_EN ; 
 int XMAC_PFC_CTRL_HI_REG_PFC_STATS_EN ; 
 int XMAC_PFC_CTRL_HI_REG_RX_PFC_EN ; 
 int XMAC_PFC_CTRL_HI_REG_TX_PFC_EN ; 
 int XMAC_REG_CTRL_SA_HI ; 
 int XMAC_REG_CTRL_SA_LO ; 
 int XMAC_REG_PAUSE_CTRL ; 
 int XMAC_REG_PFC_CTRL ; 
 int XMAC_REG_PFC_CTRL_HI ; 

__attribute__((used)) static void elink_update_pfc_xmac(struct elink_params *params,
				  struct elink_vars *vars,
				  uint8_t is_lb)
{
	struct bxe_softc *sc = params->sc;
	uint32_t xmac_base;
	uint32_t pause_val, pfc0_val, pfc1_val;

	/* XMAC base adrr */
	xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;

	/* Initialize pause and pfc registers */
	pause_val = 0x18000;
	pfc0_val = 0xFFFF8000;
	pfc1_val = 0x2;

	/* No PFC support */
	if (!(params->feature_config_flags &
	      ELINK_FEATURE_CONFIG_PFC_ENABLED)) {

		/* RX flow control - Process pause frame in receive direction
		 */
		if (vars->flow_ctrl & ELINK_FLOW_CTRL_RX)
			pause_val |= XMAC_PAUSE_CTRL_REG_RX_PAUSE_EN;

		/* TX flow control - Send pause packet when buffer is full */
		if (vars->flow_ctrl & ELINK_FLOW_CTRL_TX)
			pause_val |= XMAC_PAUSE_CTRL_REG_TX_PAUSE_EN;
	} else {/* PFC support */
		pfc1_val |= XMAC_PFC_CTRL_HI_REG_PFC_REFRESH_EN |
			XMAC_PFC_CTRL_HI_REG_PFC_STATS_EN |
			XMAC_PFC_CTRL_HI_REG_RX_PFC_EN |
			XMAC_PFC_CTRL_HI_REG_TX_PFC_EN |
			XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON;
		/* Write pause and PFC registers */
		REG_WR(sc, xmac_base + XMAC_REG_PAUSE_CTRL, pause_val);
		REG_WR(sc, xmac_base + XMAC_REG_PFC_CTRL, pfc0_val);
		REG_WR(sc, xmac_base + XMAC_REG_PFC_CTRL_HI, pfc1_val);
		pfc1_val &= ~XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON;

	}

	/* Write pause and PFC registers */
	REG_WR(sc, xmac_base + XMAC_REG_PAUSE_CTRL, pause_val);
	REG_WR(sc, xmac_base + XMAC_REG_PFC_CTRL, pfc0_val);
	REG_WR(sc, xmac_base + XMAC_REG_PFC_CTRL_HI, pfc1_val);


	/* Set MAC address for source TX Pause/PFC frames */
	REG_WR(sc, xmac_base + XMAC_REG_CTRL_SA_LO,
	       ((params->mac_addr[2] << 24) |
		(params->mac_addr[3] << 16) |
		(params->mac_addr[4] << 8) |
		(params->mac_addr[5])));
	REG_WR(sc, xmac_base + XMAC_REG_CTRL_SA_HI,
	       ((params->mac_addr[0] << 8) |
		(params->mac_addr[1])));

	DELAY(30);
}