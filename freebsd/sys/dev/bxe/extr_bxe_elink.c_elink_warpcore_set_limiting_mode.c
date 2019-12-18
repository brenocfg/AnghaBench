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
typedef  int uint16_t ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
#define  ELINK_EDC_MODE_ACTIVE_DAC 131 
#define  ELINK_EDC_MODE_LIMITING 130 
#define  ELINK_EDC_MODE_LINEAR 129 
#define  ELINK_EDC_MODE_PASSIVE_DAC 128 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE ; 
 int MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT ; 
 int MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_DAC ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_warpcore_reset_lane (struct bxe_softc*,struct elink_phy*,int) ; 

__attribute__((used)) static void elink_warpcore_set_limiting_mode(struct elink_params *params,
					     struct elink_phy *phy,
					     uint16_t edc_mode)
{
	uint16_t val = 0;
	uint16_t mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT;
	struct bxe_softc *sc = params->sc;

	uint8_t lane = elink_get_warpcore_lane(phy, params);
	/* This is a global register which controls all lanes */
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, &val);
	val &= ~(0xf << (lane << 2));

	switch (edc_mode) {
	case ELINK_EDC_MODE_LINEAR:
	case ELINK_EDC_MODE_LIMITING:
		mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT;
		break;
	case ELINK_EDC_MODE_PASSIVE_DAC:
	case ELINK_EDC_MODE_ACTIVE_DAC:
		mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_DAC;
		break;
	default:
		break;
	}

	val |= (mode << (lane << 2));
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, val);
	/* A must read */
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, &val);

	/* Restart microcode to re-read the new mode */
	elink_warpcore_reset_lane(sc, phy, 1);
	elink_warpcore_reset_lane(sc, phy, 0);

}