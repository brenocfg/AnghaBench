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
struct elink_phy {int flags; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ELINK_FLAGS_WC_DUAL_MODE ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_COMBO_IEEE0_MIICTRL ; 
 int /*<<< orphan*/  MDIO_WC_REG_IEEE0BLK_MIICNTL ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK1_LANECTRL0 ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK1_LANECTRL1 ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK1_LANECTRL2 ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_read_and_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_set_aer_mmd (struct elink_params*,struct elink_phy*) ; 
 int /*<<< orphan*/  elink_set_mdio_emac_per_phy (struct bxe_softc*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_sfp_e3_set_transmitter (struct elink_params*,struct elink_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_warpcore_reset_lane (struct bxe_softc*,struct elink_phy*,int) ; 

__attribute__((used)) static void elink_warpcore_link_reset(struct elink_phy *phy,
				      struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val16, lane;
	elink_sfp_e3_set_transmitter(params, phy, 0);
	elink_set_mdio_emac_per_phy(sc, params);
	elink_set_aer_mmd(params, phy);
	/* Global register */
	elink_warpcore_reset_lane(sc, phy, 1);

	/* Clear loopback settings (if any) */
	/* 10G & 20G */
	elink_cl45_read_and_write(sc, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_COMBO_IEEE0_MIICTRL, 0xBFFF);

	elink_cl45_read_and_write(sc, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_IEEE0BLK_MIICNTL, 0xfffe);

	/* Update those 1-copy registers */
	CL22_WR_OVER_CL45(sc, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);
	/* Enable 1G MDIO (1-copy) */
	elink_cl45_read_and_write(sc, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL,
				  ~0x10);

	elink_cl45_read_and_write(sc, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_XGXSBLK1_LANECTRL2, 0xff00);
	lane = elink_get_warpcore_lane(phy, params);
	/* Disable CL36 PCS Tx */
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_XGXSBLK1_LANECTRL0, &val16);
	val16 |= (0x11 << lane);
	if (phy->flags & ELINK_FLAGS_WC_DUAL_MODE)
		val16 |= (0x22 << lane);
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_XGXSBLK1_LANECTRL0, val16);

	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_XGXSBLK1_LANECTRL1, &val16);
	val16 &= ~(0x0303 << (lane << 1));
	val16 |= (0x0101 << (lane << 1));
	if (phy->flags & ELINK_FLAGS_WC_DUAL_MODE) {
		val16 &= ~(0x0c0c << (lane << 1));
		val16 |= (0x0404 << (lane << 1));
	}

	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_XGXSBLK1_LANECTRL1, val16);
	/* Restore AER */
	elink_set_aer_mmd(params, phy);

}