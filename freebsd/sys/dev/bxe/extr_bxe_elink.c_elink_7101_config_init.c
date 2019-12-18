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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct elink_vars {int dummy; } ;
struct elink_phy {int /*<<< orphan*/  ver_addr; } ;
struct elink_params {int /*<<< orphan*/  port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7101_VER1 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7101_VER2 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_7107_LED_CNTL ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_2 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_OUTPUT_HIGH ; 
 int /*<<< orphan*/  elink_cb_gpio_write (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_ext_phy_hw_reset (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_ext_phy_set_pause (struct elink_params*,struct elink_phy*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_save_spirom_version (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_wait_reset_complete (struct bxe_softc*,struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static elink_status_t elink_7101_config_init(struct elink_phy *phy,
				  struct elink_params *params,
				  struct elink_vars *vars)
{
	uint16_t fw_ver1, fw_ver2, val;
	struct bxe_softc *sc = params->sc;
	ELINK_DEBUG_P0(sc, "Setting the SFX7101 LASI indication\n");

	/* Restore normal power mode*/
	elink_cb_gpio_write(sc, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, params->port);
	/* HW reset */
	elink_ext_phy_hw_reset(sc, params->port);
	elink_wait_reset_complete(sc, phy, params);

	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x1);
	ELINK_DEBUG_P0(sc, "Setting the SFX7101 LED to blink on traffic\n");
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_7107_LED_CNTL, (1<<3));

	elink_ext_phy_set_pause(params, phy, vars);
	/* Restart autoneg */
	elink_cl45_read(sc, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, &val);
	val |= 0x200;
	elink_cl45_write(sc, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, val);

	/* Save spirom version */
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_7101_VER1, &fw_ver1);

	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_7101_VER2, &fw_ver2);
	elink_save_spirom_version(sc, params->port,
				  (uint32_t)(fw_ver1<<16 | fw_ver2), phy->ver_addr);
	return ELINK_STATUS_OK;
}