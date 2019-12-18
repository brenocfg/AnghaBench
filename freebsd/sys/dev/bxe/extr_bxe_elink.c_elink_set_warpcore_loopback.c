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
typedef  int uint16_t ;
struct elink_phy {int supported; int flags; int /*<<< orphan*/  req_line_speed; } ;
struct elink_params {int /*<<< orphan*/  loopback_mode; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ELINK_FLAGS_WC_DUAL_MODE ; 
 int /*<<< orphan*/  ELINK_SPEED_10000 ; 
 int ELINK_SUPPORTED_20000baseKR2_Full ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_COMBO_IEEE0_MIICTRL ; 
 int /*<<< orphan*/  MDIO_WC_REG_IEEE0BLK_MIICNTL ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK1_LANECTRL2 ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_read_or_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_set_aer_mmd (struct elink_params*,struct elink_phy*) ; 

__attribute__((used)) static void elink_set_warpcore_loopback(struct elink_phy *phy,
					struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val16;
	uint32_t lane;
	ELINK_DEBUG_P2(sc, "Setting Warpcore loopback type %x, speed %d\n",
		       params->loopback_mode, phy->req_line_speed);

	if (phy->req_line_speed < ELINK_SPEED_10000 ||
	    phy->supported & ELINK_SUPPORTED_20000baseKR2_Full) {
		/* 10/100/1000/20G-KR2 */

		/* Update those 1-copy registers */
		CL22_WR_OVER_CL45(sc, phy, MDIO_REG_BANK_AER_BLOCK,
				  MDIO_AER_BLOCK_AER_REG, 0);
		/* Enable 1G MDIO (1-copy) */
		elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_XGXSBLK0_XGXSCONTROL,
					 0x10);
		/* Set 1G loopback based on lane (1-copy) */
		lane = elink_get_warpcore_lane(phy, params);
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_XGXSBLK1_LANECTRL2, &val16);
		val16 |= (1<<lane);
		if (phy->flags & ELINK_FLAGS_WC_DUAL_MODE)
			val16 |= (2<<lane);
		elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_XGXSBLK1_LANECTRL2,
				 val16);

		/* Switch back to 4-copy registers */
		elink_set_aer_mmd(params, phy);
	} else {
		/* 10G / 20G-DXGXS */
		elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_COMBO_IEEE0_MIICTRL,
					 0x4000);
		elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x1);
	}
}