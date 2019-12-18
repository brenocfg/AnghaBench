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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct elink_phy {int /*<<< orphan*/  media_type; } ;
struct elink_params {int link_flags; int /*<<< orphan*/  port; int /*<<< orphan*/  shmem_base; int /*<<< orphan*/  chip_id; struct elink_phy* phy; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_ETH_PHY_NOT_PRESENT ; 
 size_t ELINK_EXT_PHY1 ; 
 size_t ELINK_INT_PHY ; 
 int ELINK_PHY_INITIALIZED ; 
 scalar_t__ ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_DIGITAL5_MISC6 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_HIGH ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_INT_OUTPUT_CLR ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_INT_OUTPUT_SET ; 
 int /*<<< orphan*/  elink_cb_gpio_int_write (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ elink_cb_gpio_read (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ elink_get_mod_abs_int_cfg (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elink_power_sfp_module (struct elink_params*,struct elink_phy*,int) ; 
 int /*<<< orphan*/  elink_set_aer_mmd (struct elink_params*,struct elink_phy*) ; 
 int /*<<< orphan*/  elink_set_mdio_emac_per_phy (struct bxe_softc*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_set_sfp_module_fault_led (struct elink_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_sfp_module_detection (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_sfp_set_transmitter (struct elink_params*,struct elink_phy*,int) ; 
 scalar_t__ elink_wait_for_sfp_module_initialized (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_warpcore_config_sfi (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_warpcore_reset_lane (struct bxe_softc*,struct elink_phy*,int) ; 

void elink_handle_module_detect_int(struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	struct elink_phy *phy;
	uint32_t gpio_val;
	uint8_t gpio_num, gpio_port;
	if (CHIP_IS_E3(sc)) {
		phy = &params->phy[ELINK_INT_PHY];
		/* Always enable TX laser,will be disabled in case of fault */
		elink_sfp_set_transmitter(params, phy, 1);
	} else {
		phy = &params->phy[ELINK_EXT_PHY1];
	}
	if (elink_get_mod_abs_int_cfg(sc, params->chip_id, params->shmem_base,
				      params->port, &gpio_num, &gpio_port) ==
	    ELINK_STATUS_ERROR) {
		ELINK_DEBUG_P0(sc, "Failed to get MOD_ABS interrupt config\n");
		return;
	}

	/* Set valid module led off */
	elink_set_sfp_module_fault_led(params, MISC_REGISTERS_GPIO_HIGH);

	/* Get current gpio val reflecting module plugged in / out*/
	gpio_val = elink_cb_gpio_read(sc, gpio_num, gpio_port);

	/* Call the handling function in case module is detected */
	if (gpio_val == 0) {
		elink_set_mdio_emac_per_phy(sc, params);
		elink_set_aer_mmd(params, phy);

		elink_power_sfp_module(params, phy, 1);
		elink_cb_gpio_int_write(sc, gpio_num,
				   MISC_REGISTERS_GPIO_INT_OUTPUT_CLR,
				   gpio_port);
		if (elink_wait_for_sfp_module_initialized(phy, params) == 0) {
			elink_sfp_module_detection(phy, params);
			if (CHIP_IS_E3(sc)) {
				uint16_t rx_tx_in_reset;
				/* In case WC is out of reset, reconfigure the
				 * link speed while taking into account 1G
				 * module limitation.
				 */
				elink_cl45_read(sc, phy,
						MDIO_WC_DEVAD,
						MDIO_WC_REG_DIGITAL5_MISC6,
						&rx_tx_in_reset);
				if ((!rx_tx_in_reset) &&
				    (params->link_flags &
				     ELINK_PHY_INITIALIZED)) {
					elink_warpcore_reset_lane(sc, phy, 1);
					elink_warpcore_config_sfi(phy, params);
					elink_warpcore_reset_lane(sc, phy, 0);
				}
			}
		} else {
			ELINK_DEBUG_P0(sc, "SFP+ module is not initialized\n");
		}
	} else {
		elink_cb_gpio_int_write(sc, gpio_num,
				   MISC_REGISTERS_GPIO_INT_OUTPUT_SET,
				   gpio_port);
		/* Module was plugged out.
		 * Disable transmit for this module
		 */
		phy->media_type = ELINK_ETH_PHY_NOT_PRESENT;
	}
}