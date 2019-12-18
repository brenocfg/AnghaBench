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
struct mv88e61xxphy_softc {struct mv88e61xxphy_port_softc* sc_ports; } ;
struct mv88e61xxphy_port_softc {int sc_vlan; scalar_t__ sc_port; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E61XXPHY_PORT_FLAG_VTU_UPDATE ; 
 int /*<<< orphan*/  MV88E61XXPHY_VTU_DISCARDED ; 
 int /*<<< orphan*/  MV88E61XXPHY_VTU_TAGGED ; 
 int /*<<< orphan*/  MV88E61XXPHY_VTU_UNTAGGED ; 
 int /*<<< orphan*/  MV88E61XX_GLOBAL ; 
 int /*<<< orphan*/  MV88E61XX_GLOBAL_VTU_OP ; 
 int MV88E61XX_GLOBAL_VTU_OP_BUSY ; 
 int MV88E61XX_GLOBAL_VTU_OP_OP_VTU_LOAD ; 
 int /*<<< orphan*/  MV88E61XX_GLOBAL_VTU_VID ; 
 int MV88E61XX_GLOBAL_VTU_VID_VALID ; 
 scalar_t__ MV88E61XX_HOST_PORT ; 
 unsigned int MV88E61XX_PORTS ; 
 int /*<<< orphan*/  MV88E61XX_WRITE (struct mv88e61xxphy_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv88e61xxphy_vtu_set_membership (struct mv88e61xxphy_softc*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e61xxphy_vtu_wait (struct mv88e61xxphy_softc*) ; 

__attribute__((used)) static void
mv88e61xxphy_vtu_load(struct mv88e61xxphy_softc *sc, uint16_t vid)
{
	unsigned port;

	/*
	 * Wait for previous operation to complete.
	 */
	mv88e61xxphy_vtu_wait(sc);

	/*
	 * Set VID.
	 */
	MV88E61XX_WRITE(sc, MV88E61XX_GLOBAL, MV88E61XX_GLOBAL_VTU_VID,
	    MV88E61XX_GLOBAL_VTU_VID_VALID | vid);

	/*
	 * Add ports to this VTU.
	 */
	for (port = 0; port < MV88E61XX_PORTS; port++) {
		struct mv88e61xxphy_port_softc *psc;

		psc = &sc->sc_ports[port];
		if (psc->sc_vlan == vid) {
			/*
			 * Send this port its VLAN traffic untagged.
			 */
			psc->sc_flags &= ~MV88E61XXPHY_PORT_FLAG_VTU_UPDATE;
			mv88e61xxphy_vtu_set_membership(sc, port, MV88E61XXPHY_VTU_UNTAGGED);
		} else if (psc->sc_port == MV88E61XX_HOST_PORT) {
			/*
			 * The host sees all VLANs tagged.
			 */
			mv88e61xxphy_vtu_set_membership(sc, port, MV88E61XXPHY_VTU_TAGGED);
		} else {
			/*
			 * This port isn't on this VLAN.
			 */
			mv88e61xxphy_vtu_set_membership(sc, port, MV88E61XXPHY_VTU_DISCARDED);
		}
	}

	/*
	 * Start adding this entry.
	 */
	MV88E61XX_WRITE(sc, MV88E61XX_GLOBAL, MV88E61XX_GLOBAL_VTU_OP,
	    MV88E61XX_GLOBAL_VTU_OP_BUSY |
	    MV88E61XX_GLOBAL_VTU_OP_OP_VTU_LOAD);
}