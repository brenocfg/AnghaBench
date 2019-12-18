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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct elink_vars {int /*<<< orphan*/  link_up; } ;
struct elink_params {size_t port; int hw_led_mode; int feature_config_flags; int num_phys; TYPE_1__* phy; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  (* set_link_led ) (TYPE_1__*,struct elink_params*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,size_t) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 size_t ELINK_EXT_PHY1 ; 
 int ELINK_FEATURE_CONFIG_EMUL_DISABLE_EMAC ; 
#define  ELINK_LED_MODE_FRONT_PANEL_OFF 131 
#define  ELINK_LED_MODE_OFF 130 
#define  ELINK_LED_MODE_ON 129 
#define  ELINK_LED_MODE_OPER 128 
 size_t ELINK_MAX_PHYS ; 
 int /*<<< orphan*/  ELINK_SINGLE_MEDIA_DIRECT (struct elink_params*) ; 
 int ELINK_SPEED_10 ; 
 int ELINK_SPEED_100 ; 
 int ELINK_SPEED_1000 ; 
 int ELINK_SPEED_10000 ; 
 int ELINK_SPEED_2500 ; 
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int EMAC_LED_1000MB_OVERRIDE ; 
 int EMAC_LED_100MB_OVERRIDE ; 
 int EMAC_LED_10MB_OVERRIDE ; 
 int EMAC_LED_OVERRIDE ; 
 int EMAC_REG_EMAC_LED ; 
 int GRCBASE_EMAC0 ; 
 int GRCBASE_EMAC1 ; 
 int LED_BLINK_RATE_VAL_E1X_E2 ; 
 int LED_BLINK_RATE_VAL_E3 ; 
 size_t NIG_REG_LED_10G_P0 ; 
 size_t NIG_REG_LED_CONTROL_BLINK_RATE_ENA_P0 ; 
 size_t NIG_REG_LED_CONTROL_BLINK_RATE_P0 ; 
 size_t NIG_REG_LED_CONTROL_BLINK_TRAFFIC_P0 ; 
 size_t NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0 ; 
 size_t NIG_REG_LED_CONTROL_TRAFFIC_P0 ; 
 size_t NIG_REG_LED_MODE_P0 ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,size_t,int) ; 
 int SHARED_HW_CFG_LED_EXTPHY2 ; 
 int SHARED_HW_CFG_LED_MAC1 ; 
 int SHARED_HW_CFG_LED_MODE_SHIFT ; 
 int SHARED_HW_CFG_LED_PHY1 ; 
 int elink_cb_reg_read (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  elink_cb_reg_write (struct bxe_softc*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct elink_params*,size_t) ; 

elink_status_t elink_set_led(struct elink_params *params,
		  struct elink_vars *vars, uint8_t mode, uint32_t speed)
{
	uint8_t port = params->port;
	uint16_t hw_led_mode = params->hw_led_mode;
	elink_status_t rc = ELINK_STATUS_OK;
	uint8_t phy_idx;
	uint32_t tmp;
	uint32_t emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	struct bxe_softc *sc = params->sc;
	ELINK_DEBUG_P2(sc, "elink_set_led: port %x, mode %d\n", port, mode);
	ELINK_DEBUG_P2(sc, "speed 0x%x, hw_led_mode 0x%x\n",
		 speed, hw_led_mode);
	/* In case */
	for (phy_idx = ELINK_EXT_PHY1; phy_idx < ELINK_MAX_PHYS; phy_idx++) {
		if (params->phy[phy_idx].set_link_led) {
			params->phy[phy_idx].set_link_led(
				&params->phy[phy_idx], params, mode);
		}
	}
#ifdef ELINK_INCLUDE_EMUL
	if (params->feature_config_flags &
	    ELINK_FEATURE_CONFIG_EMUL_DISABLE_EMAC)
		return rc;
#endif

	switch (mode) {
	case ELINK_LED_MODE_FRONT_PANEL_OFF:
	case ELINK_LED_MODE_OFF:
		REG_WR(sc, NIG_REG_LED_10G_P0 + port*4, 0);
		REG_WR(sc, NIG_REG_LED_MODE_P0 + port*4,
		       SHARED_HW_CFG_LED_MAC1);

		tmp = elink_cb_reg_read(sc, emac_base + EMAC_REG_EMAC_LED);
		if (params->phy[ELINK_EXT_PHY1].type ==
			PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE)
			tmp &= ~(EMAC_LED_1000MB_OVERRIDE |
				EMAC_LED_100MB_OVERRIDE |
				EMAC_LED_10MB_OVERRIDE);
		else
			tmp |= EMAC_LED_OVERRIDE;

		elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_LED, tmp);
		break;

	case ELINK_LED_MODE_OPER:
		/* For all other phys, OPER mode is same as ON, so in case
		 * link is down, do nothing
		 */
		if (!vars->link_up)
			break;
	case ELINK_LED_MODE_ON:
		if (((params->phy[ELINK_EXT_PHY1].type ==
			  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727) ||
			 (params->phy[ELINK_EXT_PHY1].type ==
			  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722)) &&
		    CHIP_IS_E2(sc) && params->num_phys == 2) {
			/* This is a work-around for E2+8727 Configurations */
			if (mode == ELINK_LED_MODE_ON ||
				speed == ELINK_SPEED_10000){
				REG_WR(sc, NIG_REG_LED_MODE_P0 + port*4, 0);
				REG_WR(sc, NIG_REG_LED_10G_P0 + port*4, 1);

				tmp = elink_cb_reg_read(sc, emac_base + EMAC_REG_EMAC_LED);
				elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_LED,
					(tmp | EMAC_LED_OVERRIDE));
				/* Return here without enabling traffic
				 * LED blink and setting rate in ON mode.
				 * In oper mode, enabling LED blink
				 * and setting rate is needed.
				 */
				if (mode == ELINK_LED_MODE_ON)
					return rc;
			}
		} else if (ELINK_SINGLE_MEDIA_DIRECT(params)) {
			/* This is a work-around for HW issue found when link
			 * is up in CL73
			 */
			if ((!CHIP_IS_E3(sc)) ||
			    (CHIP_IS_E3(sc) &&
			     mode == ELINK_LED_MODE_ON))
				REG_WR(sc, NIG_REG_LED_10G_P0 + port*4, 1);

			if (CHIP_IS_E1x(sc) ||
			    CHIP_IS_E2(sc) ||
			    (mode == ELINK_LED_MODE_ON))
				REG_WR(sc, NIG_REG_LED_MODE_P0 + port*4, 0);
			else
				REG_WR(sc, NIG_REG_LED_MODE_P0 + port*4,
				       hw_led_mode);
		} else if ((params->phy[ELINK_EXT_PHY1].type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE) &&
			   (mode == ELINK_LED_MODE_ON)) {
			REG_WR(sc, NIG_REG_LED_MODE_P0 + port*4, 0);
			tmp = elink_cb_reg_read(sc, emac_base + EMAC_REG_EMAC_LED);
			elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_LED, tmp |
				EMAC_LED_OVERRIDE | EMAC_LED_1000MB_OVERRIDE);
			/* Break here; otherwise, it'll disable the
			 * intended override.
			 */
			break;
		} else {
			uint32_t nig_led_mode = ((params->hw_led_mode <<
					     SHARED_HW_CFG_LED_MODE_SHIFT) ==
					    SHARED_HW_CFG_LED_EXTPHY2) ?
				(SHARED_HW_CFG_LED_PHY1 >>
				 SHARED_HW_CFG_LED_MODE_SHIFT) : hw_led_mode;
			REG_WR(sc, NIG_REG_LED_MODE_P0 + port*4,
			       nig_led_mode);
		}

		REG_WR(sc, NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0 + port*4, 0);
		/* Set blinking rate to ~15.9Hz */
		if (CHIP_IS_E3(sc))
			REG_WR(sc, NIG_REG_LED_CONTROL_BLINK_RATE_P0 + port*4,
			       LED_BLINK_RATE_VAL_E3);
		else
			REG_WR(sc, NIG_REG_LED_CONTROL_BLINK_RATE_P0 + port*4,
			       LED_BLINK_RATE_VAL_E1X_E2);
		REG_WR(sc, NIG_REG_LED_CONTROL_BLINK_RATE_ENA_P0 +
		       port*4, 1);
		tmp = elink_cb_reg_read(sc, emac_base + EMAC_REG_EMAC_LED);
		elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_LED,
			(tmp & (~EMAC_LED_OVERRIDE)));

		if (CHIP_IS_E1(sc) &&
		    ((speed == ELINK_SPEED_2500) ||
		     (speed == ELINK_SPEED_1000) ||
		     (speed == ELINK_SPEED_100) ||
		     (speed == ELINK_SPEED_10))) {
			/* For speeds less than 10G LED scheme is different */
			REG_WR(sc, NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0
			       + port*4, 1);
			REG_WR(sc, NIG_REG_LED_CONTROL_TRAFFIC_P0 +
			       port*4, 0);
			REG_WR(sc, NIG_REG_LED_CONTROL_BLINK_TRAFFIC_P0 +
			       port*4, 1);
		}
		break;

	default:
		rc = ELINK_STATUS_ERROR;
		ELINK_DEBUG_P1(sc, "elink_set_led: Invalid led mode %d\n",
			 mode);
		break;
	}
	return rc;

}