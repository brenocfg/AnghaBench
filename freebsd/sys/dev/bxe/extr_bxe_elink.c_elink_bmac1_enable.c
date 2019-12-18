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
typedef  int uint32_t ;
struct elink_vars {int dummy; } ;
struct elink_params {int* mac_addr; scalar_t__ port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int BIGMAC_REGISTER_BMAC_CONTROL ; 
 int BIGMAC_REGISTER_BMAC_XGXS_CONTROL ; 
 int BIGMAC_REGISTER_CNT_MAX_SIZE ; 
 int BIGMAC_REGISTER_RX_LLFC_MSG_FLDS ; 
 int BIGMAC_REGISTER_RX_MAX_SIZE ; 
 int BIGMAC_REGISTER_TX_MAX_SIZE ; 
 int BIGMAC_REGISTER_TX_PAUSE_THRESHOLD ; 
 int BIGMAC_REGISTER_TX_SOURCE_ADDR ; 
 scalar_t__ CHIP_REV_IS_EMUL (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int ELINK_ETH_MAX_JUMBO_PACKET_SIZE ; 
 int ELINK_ETH_OVREHEAD ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int NIG_REG_INGRESS_BMAC0_MEM ; 
 int NIG_REG_INGRESS_BMAC1_MEM ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bxe_softc*,int,int*,int) ; 
 int /*<<< orphan*/  elink_update_pfc_bmac1 (struct elink_params*,struct elink_vars*) ; 

__attribute__((used)) static elink_status_t elink_bmac1_enable(struct elink_params *params,
			      struct elink_vars *vars,
			      uint8_t is_lb)
{
	struct bxe_softc *sc = params->sc;
	uint8_t port = params->port;
	uint32_t bmac_addr = port ? NIG_REG_INGRESS_BMAC1_MEM :
			       NIG_REG_INGRESS_BMAC0_MEM;
	uint32_t wb_data[2];
	uint32_t val;

	ELINK_DEBUG_P0(sc, "Enabling BigMAC1\n");

	/* XGXS control */
	wb_data[0] = 0x3c;
	wb_data[1] = 0;
	REG_WR_DMAE(sc, bmac_addr + BIGMAC_REGISTER_BMAC_XGXS_CONTROL,
		    wb_data, 2);

	/* TX MAC SA */
	wb_data[0] = ((params->mac_addr[2] << 24) |
		       (params->mac_addr[3] << 16) |
		       (params->mac_addr[4] << 8) |
			params->mac_addr[5]);
	wb_data[1] = ((params->mac_addr[0] << 8) |
			params->mac_addr[1]);
	REG_WR_DMAE(sc, bmac_addr + BIGMAC_REGISTER_TX_SOURCE_ADDR, wb_data, 2);

	/* MAC control */
	val = 0x3;
	if (is_lb) {
		val |= 0x4;
		ELINK_DEBUG_P0(sc,  "enable bmac loopback\n");
	}
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(sc, bmac_addr + BIGMAC_REGISTER_BMAC_CONTROL, wb_data, 2);

	/* Set rx mtu */
	wb_data[0] = ELINK_ETH_MAX_JUMBO_PACKET_SIZE + ELINK_ETH_OVREHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(sc, bmac_addr + BIGMAC_REGISTER_RX_MAX_SIZE, wb_data, 2);

	elink_update_pfc_bmac1(params, vars);

	/* Set tx mtu */
	wb_data[0] = ELINK_ETH_MAX_JUMBO_PACKET_SIZE + ELINK_ETH_OVREHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(sc, bmac_addr + BIGMAC_REGISTER_TX_MAX_SIZE, wb_data, 2);

	/* Set cnt max size */
	wb_data[0] = ELINK_ETH_MAX_JUMBO_PACKET_SIZE + ELINK_ETH_OVREHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(sc, bmac_addr + BIGMAC_REGISTER_CNT_MAX_SIZE, wb_data, 2);

	/* Configure SAFC */
	wb_data[0] = 0x1000200;
	wb_data[1] = 0;
	REG_WR_DMAE(sc, bmac_addr + BIGMAC_REGISTER_RX_LLFC_MSG_FLDS,
		    wb_data, 2);
#ifdef ELINK_INCLUDE_EMUL
	/* Fix for emulation */
	if (CHIP_REV_IS_EMUL(sc)) {
		wb_data[0] = 0xf000;
		wb_data[1] = 0;
		REG_WR_DMAE(sc,	bmac_addr + BIGMAC_REGISTER_TX_PAUSE_THRESHOLD,
			    wb_data, 2);
	}
#endif

	return ELINK_STATUS_OK;
}