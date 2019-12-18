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
struct axe_softc {scalar_t__ sc_phyno; int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 scalar_t__ AXE_772_PHY_NO_EPHY ; 
 int /*<<< orphan*/  AXE_CMD_RXCTL_WRITE ; 
 int /*<<< orphan*/  AXE_CMD_SW_PHY_SELECT ; 
 int /*<<< orphan*/  AXE_CMD_SW_RESET_REG ; 
 int /*<<< orphan*/  AXE_CMD_WRITE_GPIO ; 
 int AXE_SW_RESET_CLEAR ; 
 int AXE_SW_RESET_IPPD ; 
 int AXE_SW_RESET_IPRL ; 
 int AXE_SW_RESET_PRL ; 
 int /*<<< orphan*/  axe_cmd (struct axe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  uether_pause (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
axe_ax88772_init(struct axe_softc *sc)
{
	axe_cmd(sc, AXE_CMD_WRITE_GPIO, 0, 0x00b0, NULL);
	uether_pause(&sc->sc_ue, hz / 16);

	if (sc->sc_phyno == AXE_772_PHY_NO_EPHY) {
		/* ask for the embedded PHY */
		axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, 0x01, NULL);
		uether_pause(&sc->sc_ue, hz / 64);

		/* power down and reset state, pin reset state */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_CLEAR, NULL);
		uether_pause(&sc->sc_ue, hz / 16);

		/* power down/reset state, pin operating state */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_IPPD | AXE_SW_RESET_PRL, NULL);
		uether_pause(&sc->sc_ue, hz / 4);

		/* power up, reset */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_PRL, NULL);

		/* power up, operating */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_IPRL | AXE_SW_RESET_PRL, NULL);
	} else {
		/* ask for external PHY */
		axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, 0x00, NULL);
		uether_pause(&sc->sc_ue, hz / 64);

		/* power down internal PHY */
		axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
		    AXE_SW_RESET_IPPD | AXE_SW_RESET_PRL, NULL);
	}

	uether_pause(&sc->sc_ue, hz / 4);
	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, 0, NULL);
}