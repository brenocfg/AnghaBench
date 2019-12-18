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
struct mv88e61xxphy_softc {struct mv88e61xxphy_port_softc* sc_ports; } ;
struct mv88e61xxphy_port_softc {int sc_flags; scalar_t__ sc_vlan; } ;

/* Variables and functions */
 int MV88E61XXPHY_PORT_FLAG_VTU_UPDATE ; 
 int /*<<< orphan*/  MV88E61XX_GLOBAL ; 
 int /*<<< orphan*/  MV88E61XX_GLOBAL_VTU_OP ; 
 int MV88E61XX_GLOBAL_VTU_OP_BUSY ; 
 int MV88E61XX_GLOBAL_VTU_OP_OP_FLUSH ; 
 unsigned int MV88E61XX_PORTS ; 
 int /*<<< orphan*/  MV88E61XX_WRITE (struct mv88e61xxphy_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv88e61xxphy_vtu_load (struct mv88e61xxphy_softc*,scalar_t__) ; 
 int /*<<< orphan*/  mv88e61xxphy_vtu_wait (struct mv88e61xxphy_softc*) ; 

__attribute__((used)) static void
mv88e61xxphy_init_vtu(struct mv88e61xxphy_softc *sc)
{
	unsigned port;

	/*
	 * Start flush of the VTU.
	 */
	mv88e61xxphy_vtu_wait(sc);
	MV88E61XX_WRITE(sc, MV88E61XX_GLOBAL, MV88E61XX_GLOBAL_VTU_OP,
	    MV88E61XX_GLOBAL_VTU_OP_BUSY | MV88E61XX_GLOBAL_VTU_OP_OP_FLUSH);

	/*
	 * Queue each port's VLAN to be programmed.
	 */
	for (port = 0; port < MV88E61XX_PORTS; port++) {
		struct mv88e61xxphy_port_softc *psc;

		psc = &sc->sc_ports[port];
		psc->sc_flags &= ~MV88E61XXPHY_PORT_FLAG_VTU_UPDATE;
		if (psc->sc_vlan == 0)
			continue;
		psc->sc_flags |= MV88E61XXPHY_PORT_FLAG_VTU_UPDATE;
	}

	/*
	 * Program each VLAN that is in use.
	 */
	for (port = 0; port < MV88E61XX_PORTS; port++) {
		struct mv88e61xxphy_port_softc *psc;

		psc = &sc->sc_ports[port];
		if ((psc->sc_flags & MV88E61XXPHY_PORT_FLAG_VTU_UPDATE) == 0)
			continue;
		mv88e61xxphy_vtu_load(sc, psc->sc_vlan);
	}

	/*
	 * Wait for last pending VTU operation to complete.
	 */
	mv88e61xxphy_vtu_wait(sc);
}