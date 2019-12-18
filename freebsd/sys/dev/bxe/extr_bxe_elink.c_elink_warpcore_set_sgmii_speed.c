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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct elink_phy {int req_line_speed; scalar_t__ req_duplex; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
#define  ELINK_SPEED_10 130 
#define  ELINK_SPEED_100 129 
#define  ELINK_SPEED_1000 128 
 int ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_COMBO_IEEE0_MIICTRL ; 
 int /*<<< orphan*/  MDIO_WC_REG_RX66_CONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1 ; 
 int /*<<< orphan*/  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2 ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_read_and_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_read_or_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_warpcore_set_lpi_passthrough (struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static void elink_warpcore_set_sgmii_speed(struct elink_phy *phy,
					   struct elink_params *params,
					   uint8_t fiber_mode,
					   uint8_t always_autoneg)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val16, digctrl_kx1, digctrl_kx2;

	/* Clear XFI clock comp in non-10G single lane mode. */
	elink_cl45_read_and_write(sc, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_RX66_CONTROL, ~(3<<13));

	elink_warpcore_set_lpi_passthrough(phy, params);

	if (always_autoneg || phy->req_line_speed == ELINK_SPEED_AUTO_NEG) {
		/* SGMII Autoneg */
		elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_COMBO_IEEE0_MIICTRL,
					 0x1000);
		ELINK_DEBUG_P0(sc, "set SGMII AUTONEG\n");
	} else {
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, &val16);
		val16 &= 0xcebf;
		switch (phy->req_line_speed) {
		case ELINK_SPEED_10:
			break;
		case ELINK_SPEED_100:
			val16 |= 0x2000;
			break;
		case ELINK_SPEED_1000:
			val16 |= 0x0040;
			break;
		default:
			ELINK_DEBUG_P1(sc,
			   "Speed not supported: 0x%x\n", phy->req_line_speed);
			return;
		}

		if (phy->req_duplex == DUPLEX_FULL)
			val16 |= 0x0100;

		elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, val16);

		ELINK_DEBUG_P1(sc, "set SGMII force speed %d\n",
			       phy->req_line_speed);
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, &val16);
		ELINK_DEBUG_P1(sc, "  (readback) %x\n", val16);
	}

	/* SGMII Slave mode and disable signal detect */
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1, &digctrl_kx1);
	if (fiber_mode)
		digctrl_kx1 = 1;
	else
		digctrl_kx1 &= 0xff4a;

	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			digctrl_kx1);

	/* Turn off parallel detect */
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2, &digctrl_kx2);
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			(digctrl_kx2 & ~(1<<2)));

	/* Re-enable parallel detect */
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			(digctrl_kx2 | (1<<2)));

	/* Enable autodet */
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			(digctrl_kx1 | 0x10));
}