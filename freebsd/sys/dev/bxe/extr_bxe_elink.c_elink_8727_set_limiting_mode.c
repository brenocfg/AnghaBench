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
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_PHY_IDENTIFIER ; 
 int /*<<< orphan*/  MDIO_PMA_REG_ROM_VER2 ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static elink_status_t elink_8727_set_limiting_mode(struct bxe_softc *sc,
					struct elink_phy *phy,
					uint16_t edc_mode)
{
	uint16_t phy_identifier;
	uint16_t rom_ver2_val;
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_PHY_IDENTIFIER,
			&phy_identifier);

	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_PHY_IDENTIFIER,
			 (phy_identifier & ~(1<<9)));

	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_ROM_VER2,
			&rom_ver2_val);
	/* Keep the MSB 8-bits, and set the LSB 8-bits with the edc_mode */
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_ROM_VER2,
			 (rom_ver2_val & 0xff00) | (edc_mode & 0x00ff));

	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_PHY_IDENTIFIER,
			 (phy_identifier | (1<<9)));

	return ELINK_STATUS_OK;
}