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
typedef  int uint16_t ;
struct elink_phy {scalar_t__ req_line_speed; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 int MDIO_AER_BLOCK_AER_REG ; 
 int MDIO_CL73_IEEEB0_CL73_AN_CONTROL ; 
 int MDIO_COMBO_IEEE0_MII_CONTROL ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_LOOPBACK ; 
 scalar_t__ MDIO_REG_BANK_AER_BLOCK ; 
 scalar_t__ MDIO_REG_BANK_CL73_IEEEB0 ; 
 scalar_t__ MDIO_REG_BANK_COMBO_IEEE0 ; 
 scalar_t__ NIG_REG_XGXS0_CTRL_MD_DEVAD ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_set_aer_mmd (struct elink_params*,struct elink_phy*) ; 

__attribute__((used)) static void elink_set_xgxs_loopback(struct elink_phy *phy,
				    struct elink_params *params)
{
	uint8_t port = params->port;
	struct bxe_softc *sc = params->sc;

	if (phy->req_line_speed != ELINK_SPEED_1000) {
		uint32_t md_devad = 0;

		ELINK_DEBUG_P0(sc, "XGXS 10G loopback enable\n");

		if (!CHIP_IS_E3(sc)) {
			/* Change the uni_phy_addr in the nig */
			md_devad = REG_RD(sc, (NIG_REG_XGXS0_CTRL_MD_DEVAD +
					       port*0x18));

			REG_WR(sc, NIG_REG_XGXS0_CTRL_MD_DEVAD + port*0x18,
			       0x5);
		}

		elink_cl45_write(sc, phy,
				 5,
				 (MDIO_REG_BANK_AER_BLOCK +
				  (MDIO_AER_BLOCK_AER_REG & 0xf)),
				 0x2800);

		elink_cl45_write(sc, phy,
				 5,
				 (MDIO_REG_BANK_CL73_IEEEB0 +
				  (MDIO_CL73_IEEEB0_CL73_AN_CONTROL & 0xf)),
				 0x6041);
		DELAY(1000 * 200);
		/* Set aer mmd back */
		elink_set_aer_mmd(params, phy);

		if (!CHIP_IS_E3(sc)) {
			/* And md_devad */
			REG_WR(sc, NIG_REG_XGXS0_CTRL_MD_DEVAD + port*0x18,
			       md_devad);
		}
	} else {
		uint16_t mii_ctrl;
		ELINK_DEBUG_P0(sc, "XGXS 1G loopback enable\n");
		elink_cl45_read(sc, phy, 5,
				(MDIO_REG_BANK_COMBO_IEEE0 +
				(MDIO_COMBO_IEEE0_MII_CONTROL & 0xf)),
				&mii_ctrl);
		elink_cl45_write(sc, phy, 5,
				 (MDIO_REG_BANK_COMBO_IEEE0 +
				 (MDIO_COMBO_IEEE0_MII_CONTROL & 0xf)),
				 mii_ctrl |
				 MDIO_COMBO_IEEO_MII_CONTROL_LOOPBACK);
	}
}