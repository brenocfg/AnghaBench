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
typedef  int uint16_t ;
struct elink_phy {scalar_t__ type; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_GEN_CTRL ; 
 int MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET ; 
 int MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP ; 
 int /*<<< orphan*/  MDIO_PMA_REG_M8051_MSGOUT_REG ; 
 int /*<<< orphan*/  MDIO_PMA_REG_MISC_CTRL1 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_ROM_VER1 ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073 ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_save_bcm_spirom_ver (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static elink_status_t elink_8073_8727_external_rom_boot(struct bxe_softc *sc,
					     struct elink_phy *phy,
					     uint8_t port)
{
	uint32_t count = 0;
	uint16_t fw_ver1, fw_msgout;
	elink_status_t rc = ELINK_STATUS_OK;

	/* Boot port from external ROM  */
	/* EDC grst */
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 0x0001);

	/* Ucode reboot and rst */
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 0x008c);

	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0001);

	/* Reset internal microprocessor */
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET);

	/* Release srst bit */
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP);

	/* Delay 100ms per the PHY specifications */
	DELAY(1000 * 100);

	/* 8073 sometimes taking longer to download */
	do {
		count++;
		if (count > 300) {
			ELINK_DEBUG_P2(sc,
				 "elink_8073_8727_external_rom_boot port %x:"
				 "Download failed. fw version = 0x%x\n",
				 port, fw_ver1);
			rc = ELINK_STATUS_ERROR;
			break;
		}

		elink_cl45_read(sc, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_ROM_VER1, &fw_ver1);
		elink_cl45_read(sc, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_M8051_MSGOUT_REG, &fw_msgout);

		DELAY(1000 * 1);
	} while (fw_ver1 == 0 || fw_ver1 == 0x4321 ||
			((fw_msgout & 0xff) != 0x03 && (phy->type ==
			PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073)));

	/* Clear ser_boot_ctl bit */
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0000);
	elink_save_bcm_spirom_ver(sc, phy, port);

	ELINK_DEBUG_P2(sc,
		 "elink_8073_8727_external_rom_boot port %x:"
		 "Download complete. fw version = 0x%x\n",
		 port, fw_ver1);

	return rc;
}