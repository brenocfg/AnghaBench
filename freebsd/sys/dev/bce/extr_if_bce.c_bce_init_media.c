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
struct bce_softc {int bce_phy_flags; int /*<<< orphan*/  bce_phy_addr; int /*<<< orphan*/  bce_dev; } ;

/* Variables and functions */
 int BCE_PHY_IEEE_CLAUSE_45_FLAG ; 
 int BCE_PHY_REMOTE_CAP_FLAG ; 
 int /*<<< orphan*/  BRGPHY_ADDR_EXT ; 
 int /*<<< orphan*/  BRGPHY_ADDR_EXT_AN_MMD ; 
 int /*<<< orphan*/  BRGPHY_BLOCK_ADDR ; 
 int /*<<< orphan*/  BRGPHY_BLOCK_ADDR_ADDR_EXT ; 
 int /*<<< orphan*/  BRGPHY_BLOCK_ADDR_COMBO_IEEE0 ; 
 int /*<<< orphan*/  bce_miibus_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bce_init_media(struct bce_softc *sc)
{
	if ((sc->bce_phy_flags & (BCE_PHY_IEEE_CLAUSE_45_FLAG |
	    BCE_PHY_REMOTE_CAP_FLAG)) == BCE_PHY_IEEE_CLAUSE_45_FLAG) {
		/*
		 * Configure 5709S/5716S PHYs to use traditional IEEE
		 * Clause 22 method. Otherwise we have no way to attach
		 * the PHY in mii(4) layer. PHY specific configuration
		 * is done in mii layer.
		 */

		/* Select auto-negotiation MMD of the PHY. */
		bce_miibus_write_reg(sc->bce_dev, sc->bce_phy_addr,
		    BRGPHY_BLOCK_ADDR, BRGPHY_BLOCK_ADDR_ADDR_EXT);
		bce_miibus_write_reg(sc->bce_dev, sc->bce_phy_addr,
		    BRGPHY_ADDR_EXT, BRGPHY_ADDR_EXT_AN_MMD);

		/* Set IEEE0 block of AN MMD (assumed in brgphy(4) code). */
		bce_miibus_write_reg(sc->bce_dev, sc->bce_phy_addr,
		    BRGPHY_BLOCK_ADDR, BRGPHY_BLOCK_ADDR_COMBO_IEEE0);
	}
}