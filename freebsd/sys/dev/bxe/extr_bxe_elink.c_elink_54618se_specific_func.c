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
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
#define  ELINK_PHY_INIT 128 
 int /*<<< orphan*/  MDIO_REG_GPHY_SHADOW ; 
 int MDIO_REG_GPHY_SHADOW_LED_SEL2 ; 
 int MDIO_REG_GPHY_SHADOW_WR_ENA ; 
 int /*<<< orphan*/  MDIO_REG_INTR_MASK ; 
 int MDIO_REG_INTR_MASK_LINK_STATUS ; 
 int /*<<< orphan*/  elink_cl22_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl22_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void elink_54618se_specific_func(struct elink_phy *phy,
					struct elink_params *params,
					uint32_t action)
{
	struct bxe_softc *sc = params->sc;
	uint16_t temp;
	switch (action) {
	case ELINK_PHY_INIT:
		/* Configure LED4: set to INTR (0x6). */
		/* Accessing shadow register 0xe. */
		elink_cl22_write(sc, phy,
				 MDIO_REG_GPHY_SHADOW,
				 MDIO_REG_GPHY_SHADOW_LED_SEL2);
		elink_cl22_read(sc, phy,
				MDIO_REG_GPHY_SHADOW,
				&temp);
		temp &= ~(0xf << 4);
		temp |= (0x6 << 4);
		elink_cl22_write(sc, phy,
				 MDIO_REG_GPHY_SHADOW,
				 MDIO_REG_GPHY_SHADOW_WR_ENA | temp);
		/* Configure INTR based on link status change. */
		elink_cl22_write(sc, phy,
				 MDIO_REG_INTR_MASK,
				 ~MDIO_REG_INTR_MASK_LINK_STATUS);
		break;
	}
}