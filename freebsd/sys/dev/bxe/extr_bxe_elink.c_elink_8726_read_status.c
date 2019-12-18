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
struct elink_vars {scalar_t__ line_speed; } ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_PHY_IDENTIFIER ; 
 scalar_t__ elink_8706_8726_read_status (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static uint8_t elink_8726_read_status(struct elink_phy *phy,
				 struct elink_params *params,
				 struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val1;
	uint8_t link_up = elink_8706_8726_read_status(phy, params, vars);
	if (link_up) {
		elink_cl45_read(sc, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER,
				&val1);
		if (val1 & (1<<15)) {
			ELINK_DEBUG_P0(sc, "Tx is disabled\n");
			link_up = 0;
			vars->line_speed = 0;
		}
	}
	return link_up;
}