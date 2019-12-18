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
struct elink_vars {scalar_t__ phy_link_up; } ;
struct elink_params {int port; scalar_t__ switch_cfg; int lane_config; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int ELINK_NIG_STATUS_SERDES0_LINK_STATUS ; 
 int ELINK_NIG_STATUS_XGXS0_LINK10G ; 
 int ELINK_NIG_STATUS_XGXS0_LINK_STATUS ; 
 int ELINK_NIG_STATUS_XGXS0_LINK_STATUS_SIZE ; 
 scalar_t__ ELINK_SWITCH_CFG_10G ; 
 scalar_t__ NIG_REG_STATUS_INTERRUPT_PORT0 ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT ; 
 scalar_t__ USES_WARPCORE (struct bxe_softc*) ; 
 int /*<<< orphan*/  elink_bits_dis (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_bits_en (struct bxe_softc*,scalar_t__,int) ; 

__attribute__((used)) static void elink_link_int_ack(struct elink_params *params,
			       struct elink_vars *vars, uint8_t is_10g_plus)
{
	struct bxe_softc *sc = params->sc;
	uint8_t port = params->port;
	uint32_t mask;
	/* First reset all status we assume only one line will be
	 * change at a time
	 */
	elink_bits_dis(sc, NIG_REG_STATUS_INTERRUPT_PORT0 + port*4,
		       (ELINK_NIG_STATUS_XGXS0_LINK10G |
			ELINK_NIG_STATUS_XGXS0_LINK_STATUS |
			ELINK_NIG_STATUS_SERDES0_LINK_STATUS));
	if (vars->phy_link_up) {
		if (USES_WARPCORE(sc))
			mask = ELINK_NIG_STATUS_XGXS0_LINK_STATUS;
		else {
			if (is_10g_plus)
				mask = ELINK_NIG_STATUS_XGXS0_LINK10G;
			else if (params->switch_cfg == ELINK_SWITCH_CFG_10G) {
				/* Disable the link interrupt by writing 1 to
				 * the relevant lane in the status register
				 */
				uint32_t ser_lane =
					((params->lane_config &
				    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
				    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);
				mask = ((1 << ser_lane) <<
				       ELINK_NIG_STATUS_XGXS0_LINK_STATUS_SIZE);
			} else
				mask = ELINK_NIG_STATUS_SERDES0_LINK_STATUS;
		}
		ELINK_DEBUG_P1(sc, "Ack link up interrupt with mask 0x%x\n",
			       mask);
		elink_bits_en(sc,
			      NIG_REG_STATUS_INTERRUPT_PORT0 + port*4,
			      mask);
	}
}