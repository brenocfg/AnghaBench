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
typedef  int uint32_t ;
struct elink_vars {int /*<<< orphan*/  link_status; void* flow_ctrl; } ;
struct elink_phy {int dummy; } ;
struct elink_params {void* req_fc_auto_adv; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 void* ELINK_FLOW_CTRL_BOTH ; 
 void* ELINK_FLOW_CTRL_NONE ; 
 void* ELINK_FLOW_CTRL_RX ; 
 void* ELINK_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE ; 

__attribute__((used)) static void elink_pause_resolve(struct elink_phy *phy,
				struct elink_params *params,
				struct elink_vars *vars,
				uint32_t pause_result)
{
	struct bxe_softc *sc = params->sc;
						/*  LD	    LP	 */
	switch (pause_result) {			/* ASYM P ASYM P */
	case 0xb:				/*   1  0   1  1 */
		ELINK_DEBUG_P0(sc, "Flow Control: TX only\n");
		vars->flow_ctrl = ELINK_FLOW_CTRL_TX;
		break;

	case 0xe:				/*   1  1   1  0 */
		ELINK_DEBUG_P0(sc, "Flow Control: RX only\n");
		vars->flow_ctrl = ELINK_FLOW_CTRL_RX;
		break;

	case 0x5:				/*   0  1   0  1 */
	case 0x7:				/*   0  1   1  1 */
	case 0xd:				/*   1  1   0  1 */
	case 0xf:				/*   1  1   1  1 */
		/* If the user selected to advertise RX ONLY,
		 * although we advertised both, need to enable
		 * RX only.
		 */

		if (params->req_fc_auto_adv == ELINK_FLOW_CTRL_BOTH) {
			ELINK_DEBUG_P0(sc, "Flow Control: RX & TX\n");
		vars->flow_ctrl = ELINK_FLOW_CTRL_BOTH;
		} else {
			ELINK_DEBUG_P0(sc, "Flow Control: RX only\n");
			vars->flow_ctrl = ELINK_FLOW_CTRL_RX;
		}
		break;
	default:
		ELINK_DEBUG_P0(sc, "Flow Control: None\n");
		vars->flow_ctrl = ELINK_FLOW_CTRL_NONE;
		break;
	}
	if (pause_result & (1<<0))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE;
	if (pause_result & (1<<1))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE;

}