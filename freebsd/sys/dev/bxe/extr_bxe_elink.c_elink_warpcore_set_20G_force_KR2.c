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
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_CL72_USERB0_CL72_TX_FIR_TAP ; 
 int /*<<< orphan*/  MDIO_WC_REG_CL73_USERB0_CTRL ; 
 int /*<<< orphan*/  MDIO_WC_REG_DIGITAL4_MISC3 ; 
 int /*<<< orphan*/  MDIO_WC_REG_PMD_KR_CONTROL ; 
 int /*<<< orphan*/  MDIO_WC_REG_SERDESDIGITAL_MISC1 ; 
 int /*<<< orphan*/  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_read_and_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_read_or_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_set_aer_mmd (struct elink_params*,struct elink_phy*) ; 

__attribute__((used)) static void elink_warpcore_set_20G_force_KR2(struct elink_phy *phy,
					     struct elink_params *params)
{
	uint16_t val;
	struct bxe_softc *sc = params->sc;
	/* Set global registers, so set AER lane to 0 */
	CL22_WR_OVER_CL45(sc, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);

	/* Disable sequencer */
	elink_cl45_read_and_write(sc, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL, ~(1<<13));

	elink_set_aer_mmd(params, phy);

	elink_cl45_read_and_write(sc, phy, MDIO_PMA_DEVAD,
				  MDIO_WC_REG_PMD_KR_CONTROL, ~(1<<1));
	elink_cl45_write(sc, phy, MDIO_AN_DEVAD,
			 MDIO_AN_REG_CTRL, 0);
	/* Turn off CL73 */
	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_CL73_USERB0_CTRL, &val);
	val &= ~(1<<5);
	val |= (1<<6);
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL73_USERB0_CTRL, val);

	/* Set 20G KR2 force speed */
	elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_SERDESDIGITAL_MISC1, 0x1f);

	elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DIGITAL4_MISC3, (1<<7));

	elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, &val);
	val &= ~(3<<14);
	val |= (1<<15);
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, val);
	elink_cl45_write(sc, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_TX_FIR_TAP, 0x835A);

	/* Enable sequencer (over lane 0) */
	CL22_WR_OVER_CL45(sc, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);

	elink_cl45_read_or_write(sc, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_XGXSBLK0_XGXSCONTROL, (1<<13));

	elink_set_aer_mmd(params, phy);
}