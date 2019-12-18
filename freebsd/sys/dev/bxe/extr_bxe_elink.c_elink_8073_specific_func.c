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
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
#define  ELINK_PHY_INIT 128 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXCTRL ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void elink_8073_specific_func(struct elink_phy *phy,
				     struct elink_params *params,
				     uint32_t action)
{
	struct bxe_softc *sc = params->sc;
	switch (action) {
	case ELINK_PHY_INIT:
		/* Enable LASI */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL, (1<<2));
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL,  0x0004);
		break;
	}
}