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
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int /*<<< orphan*/  MDIO_WC_REG_GP2_STATUS_GP_2_0 ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static int elink_warpcore_get_sigdet(struct elink_phy *phy,
				     struct elink_params *params)
{
	uint16_t gp2_status_reg0, lane;
	struct bxe_softc *sc = params->sc;

	lane = elink_get_warpcore_lane(phy, params);

	elink_cl45_read(sc, phy, MDIO_WC_DEVAD, MDIO_WC_REG_GP2_STATUS_GP_2_0,
				 &gp2_status_reg0);

	return (gp2_status_reg0 >> (8+lane)) & 0x1;
}