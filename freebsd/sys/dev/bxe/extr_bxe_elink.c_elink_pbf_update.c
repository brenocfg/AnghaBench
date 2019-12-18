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
typedef  scalar_t__ uint32_t ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,scalar_t__,scalar_t__) ; 
 int ELINK_ETH_MAX_JUMBO_PACKET_SIZE ; 
 int ELINK_ETH_OVREHEAD ; 
 scalar_t__ ELINK_FLOW_CTRL_RX ; 
 scalar_t__ ELINK_SPEED_10 ; 
 scalar_t__ ELINK_SPEED_100 ; 
 scalar_t__ ELINK_SPEED_1000 ; 
#define  ELINK_SPEED_10000 128 
 scalar_t__ ELINK_SPEED_2500 ; 
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 scalar_t__ PBF_REG_DISABLE_NEW_TASK_PROC_P0 ; 
 scalar_t__ PBF_REG_INIT_P0 ; 
 scalar_t__ PBF_REG_P0_ARB_THRSH ; 
 scalar_t__ PBF_REG_P0_CREDIT ; 
 scalar_t__ PBF_REG_P0_INIT_CRD ; 
 scalar_t__ PBF_REG_P0_PAUSE_ENABLE ; 
 scalar_t__ REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 

__attribute__((used)) static elink_status_t elink_pbf_update(struct elink_params *params, uint32_t flow_ctrl,
			    uint32_t line_speed)
{
	struct bxe_softc *sc = params->sc;
	uint8_t port = params->port;
	uint32_t init_crd, crd;
	uint32_t count = 1000;

	/* Disable port */
	REG_WR(sc, PBF_REG_DISABLE_NEW_TASK_PROC_P0 + port*4, 0x1);

	/* Wait for init credit */
	init_crd = REG_RD(sc, PBF_REG_P0_INIT_CRD + port*4);
	crd = REG_RD(sc, PBF_REG_P0_CREDIT + port*8);
	ELINK_DEBUG_P2(sc, "init_crd 0x%x  crd 0x%x\n", init_crd, crd);

	while ((init_crd != crd) && count) {
		DELAY(1000 * 5);
		crd = REG_RD(sc, PBF_REG_P0_CREDIT + port*8);
		count--;
	}
	crd = REG_RD(sc, PBF_REG_P0_CREDIT + port*8);
	if (init_crd != crd) {
		ELINK_DEBUG_P2(sc, "BUG! init_crd 0x%x != crd 0x%x\n",
			  init_crd, crd);
		return ELINK_STATUS_ERROR;
	}

	if (flow_ctrl & ELINK_FLOW_CTRL_RX ||
	    line_speed == ELINK_SPEED_10 ||
	    line_speed == ELINK_SPEED_100 ||
	    line_speed == ELINK_SPEED_1000 ||
	    line_speed == ELINK_SPEED_2500) {
		REG_WR(sc, PBF_REG_P0_PAUSE_ENABLE + port*4, 1);
		/* Update threshold */
		REG_WR(sc, PBF_REG_P0_ARB_THRSH + port*4, 0);
		/* Update init credit */
		init_crd = 778;		/* (800-18-4) */

	} else {
		uint32_t thresh = (ELINK_ETH_MAX_JUMBO_PACKET_SIZE +
			      ELINK_ETH_OVREHEAD)/16;
		REG_WR(sc, PBF_REG_P0_PAUSE_ENABLE + port*4, 0);
		/* Update threshold */
		REG_WR(sc, PBF_REG_P0_ARB_THRSH + port*4, thresh);
		/* Update init credit */
		switch (line_speed) {
		case ELINK_SPEED_10000:
			init_crd = thresh + 553 - 22;
			break;
		default:
			ELINK_DEBUG_P1(sc, "Invalid line_speed 0x%x\n",
				  line_speed);
			return ELINK_STATUS_ERROR;
		}
	}
	REG_WR(sc, PBF_REG_P0_INIT_CRD + port*4, init_crd);
	ELINK_DEBUG_P2(sc, "PBF updated to speed %d credit %d\n",
		 line_speed, init_crd);

	/* Probe the credit changes */
	REG_WR(sc, PBF_REG_INIT_P0 + port*4, 0x1);
	DELAY(1000 * 5);
	REG_WR(sc, PBF_REG_INIT_P0 + port*4, 0x0);

	/* Enable port */
	REG_WR(sc, PBF_REG_DISABLE_NEW_TASK_PROC_P0 + port*4, 0x0);
	return ELINK_STATUS_OK;
}