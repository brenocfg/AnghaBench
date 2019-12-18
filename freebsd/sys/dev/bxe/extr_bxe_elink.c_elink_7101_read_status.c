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
struct elink_vars {int /*<<< orphan*/  link_status; int /*<<< orphan*/  duplex; int /*<<< orphan*/  line_speed; } ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  ELINK_SPEED_10000 ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_MASTER_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_STAT ; 
 int /*<<< orphan*/  MDIO_PMA_REG_STATUS ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_ext_phy_10G_an_resolve (struct bxe_softc*,struct elink_phy*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_ext_phy_resolve_fc (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 

__attribute__((used)) static uint8_t elink_7101_read_status(struct elink_phy *phy,
				 struct elink_params *params,
				 struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint8_t link_up;
	uint16_t val1, val2;
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val2);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);
	ELINK_DEBUG_P2(sc, "10G-base-T LASI status 0x%x->0x%x\n",
		   val2, val1);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val2);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val1);
	ELINK_DEBUG_P2(sc, "10G-base-T PMA status 0x%x->0x%x\n",
		   val2, val1);
	link_up = ((val1 & 4) == 4);
	/* If link is up print the AN outcome of the SFX7101 PHY */
	if (link_up) {
		elink_cl45_read(sc, phy,
				MDIO_AN_DEVAD, MDIO_AN_REG_MASTER_STATUS,
				&val2);
		vars->line_speed = ELINK_SPEED_10000;
		vars->duplex = DUPLEX_FULL;
		ELINK_DEBUG_P2(sc, "SFX7101 AN status 0x%x->Master=%x\n",
			   val2, (val2 & (1<<14)));
		elink_ext_phy_10G_an_resolve(sc, phy, vars);
		elink_ext_phy_resolve_fc(phy, params, vars);

		/* Read LP advertised speeds */
		if (val2 & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
	}
	return link_up;
}