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
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_set_disable_pmd_transmit (struct elink_params*,struct elink_phy*,int) ; 
 int /*<<< orphan*/  elink_sfp_set_transmitter (struct elink_params*,struct elink_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_8727_link_reset(struct elink_phy *phy,
				  struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;

	/* Enable/Disable PHY transmitter output */
	elink_set_disable_pmd_transmit(params, phy, 1);

	/* Disable Transmitter */
	elink_sfp_set_transmitter(params, phy, 0);
	/* Clear LASI */
	elink_cl45_write(sc, phy, MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0);

}