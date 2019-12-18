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
struct elink_phy {int speed_cap_mask; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_OVER_1G_UP1 ; 
 int MDIO_OVER_1G_UP1_10G ; 
 int MDIO_OVER_1G_UP1_2_5G ; 
 int /*<<< orphan*/  MDIO_OVER_1G_UP3 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_OVER_1G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G ; 

__attribute__((used)) static void elink_set_brcm_cl37_advertisement(struct elink_phy *phy,
					      struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val = 0;

	/* Set extended capabilities */
	if (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G)
		val |= MDIO_OVER_1G_UP1_2_5G;
	if (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)
		val |= MDIO_OVER_1G_UP1_10G;
	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_OVER_1G,
			  MDIO_OVER_1G_UP1, val);

	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_OVER_1G,
			  MDIO_OVER_1G_UP3, 0x400);
}