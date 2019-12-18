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
typedef  int /*<<< orphan*/  uint16_t ;
struct elink_phy {int req_flow_ctrl; } ;
struct elink_params {int /*<<< orphan*/  req_fc_auto_adv; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
#define  ELINK_FLOW_CTRL_AUTO 132 
#define  ELINK_FLOW_CTRL_BOTH 131 
#define  ELINK_FLOW_CTRL_NONE 130 
#define  ELINK_FLOW_CTRL_RX 129 
#define  ELINK_FLOW_CTRL_TX 128 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_FULL_DUPLEX ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_NONE ; 

__attribute__((used)) static void elink_calc_ieee_aneg_adv(struct elink_phy *phy,
				     struct elink_params *params, uint16_t *ieee_fc)
{
	struct bxe_softc *sc = params->sc;
	*ieee_fc = MDIO_COMBO_IEEE0_AUTO_NEG_ADV_FULL_DUPLEX;
	/* Resolve pause mode and advertisement Please refer to Table
	 * 28B-3 of the 802.3ab-1999 spec
	 */

	switch (phy->req_flow_ctrl) {
	case ELINK_FLOW_CTRL_AUTO:
		switch (params->req_fc_auto_adv) {
		case ELINK_FLOW_CTRL_BOTH:
		case ELINK_FLOW_CTRL_RX:
			*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
			break;
		case ELINK_FLOW_CTRL_TX:
			*ieee_fc |=
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
			break;
		default:
			break;
		}
		break;
	case ELINK_FLOW_CTRL_TX:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
		break;

	case ELINK_FLOW_CTRL_RX:
	case ELINK_FLOW_CTRL_BOTH:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
		break;

	case ELINK_FLOW_CTRL_NONE:
	default:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_NONE;
		break;
	}
	ELINK_DEBUG_P1(sc, "ieee_fc = 0x%x\n", *ieee_fc);
}