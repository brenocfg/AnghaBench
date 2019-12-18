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
struct mv88e61xxphy_softc {int dummy; } ;
struct mv88e61xxphy_port_softc {int sc_port; int sc_domain; int sc_priority; int sc_vlan; struct mv88e61xxphy_softc* sc_switch; } ;

/* Variables and functions */
 int ETHERTYPE_VLAN ; 
 int MV88E61XX_HOST_PORT ; 
 int MV88E61XX_PORTS ; 
 int /*<<< orphan*/  MV88E61XX_PORT_CONTROL ; 
 int /*<<< orphan*/  MV88E61XX_PORT_CONTROL2 ; 
 int /*<<< orphan*/  MV88E61XX_PORT_ETHER_PROTO ; 
 int /*<<< orphan*/  MV88E61XX_PORT_FILTER ; 
 int MV88E61XX_PORT_FILTER_8021Q_SECURE ; 
 int MV88E61XX_PORT_FILTER_DISCARD_TAGGED ; 
 int MV88E61XX_PORT_FILTER_DISCARD_UNTAGGED ; 
 int MV88E61XX_PORT_FILTER_MAP_DEST ; 
 int /*<<< orphan*/  MV88E61XX_PORT_FORCE_MAC ; 
 int /*<<< orphan*/  MV88E61XX_PORT_PAUSE_CONTROL ; 
 int /*<<< orphan*/  MV88E61XX_PORT_PROVIDER_PROTO ; 
 int /*<<< orphan*/  MV88E61XX_PORT_VLAN ; 
 int /*<<< orphan*/  MV88E61XX_PORT_VLAN_MAP ; 
 int /*<<< orphan*/  MV88E61XX_WRITE_PORT (struct mv88e61xxphy_port_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mv88e61xxphy_init_port(struct mv88e61xxphy_port_softc *psc)
{
	struct mv88e61xxphy_softc *sc;
	unsigned allow_mask;

	sc = psc->sc_switch;

	/* Set media type and flow control.  */
	if (psc->sc_port != MV88E61XX_HOST_PORT) {
		/* Don't force any media type or flow control.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_FORCE_MAC, 0x0003);
	} else {
		/* Make CPU port 1G FDX.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_FORCE_MAC, 0x003e);
	}

	/* Don't limit flow control pauses.  */
	MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_PAUSE_CONTROL, 0x0000);

	/* Set various port functions per Linux.  */
	if (psc->sc_port != MV88E61XX_HOST_PORT) {
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_CONTROL, 0x04bc);
	} else {
		/*
		 * Send frames for unknown unicast and multicast groups to
		 * host, too.
		 */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_CONTROL, 0x063f);
	}

	if (psc->sc_port != MV88E61XX_HOST_PORT) {
		/* Disable trunking.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_CONTROL2, 0x0000);
	} else {
		/* Disable trunking and send learn messages to host.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_CONTROL2, 0x8000);
	}

	/*
	 * Port-based VLAN map; isolates MAC tables and forces ports to talk
	 * only to the host.
	 *
	 * Always allow the host to send to all ports and allow all ports to
	 * send to the host.
	 */
	if (psc->sc_port != MV88E61XX_HOST_PORT) {
		allow_mask = 1 << MV88E61XX_HOST_PORT;
	} else {
		allow_mask = (1 << MV88E61XX_PORTS) - 1;
		allow_mask &= ~(1 << MV88E61XX_HOST_PORT);
	}
	MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_VLAN_MAP,
	    (psc->sc_domain << 12) | allow_mask);

	/* VLAN tagging.  Set default priority and VLAN tag (or none.)  */
	MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_VLAN,
	    (psc->sc_priority << 14) | psc->sc_vlan);

	if (psc->sc_port == MV88E61XX_HOST_PORT) {
		/* Set provider ingress tag.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_PROVIDER_PROTO,
		    ETHERTYPE_VLAN);

		/* Set provider egress tag.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_ETHER_PROTO,
		    ETHERTYPE_VLAN);

		/* Use secure 802.1q mode and accept only tagged frames.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_FILTER,
		    MV88E61XX_PORT_FILTER_MAP_DEST |
		    MV88E61XX_PORT_FILTER_8021Q_SECURE |
		    MV88E61XX_PORT_FILTER_DISCARD_UNTAGGED);
	} else {
		/* Don't allow tagged frames.  */
		MV88E61XX_WRITE_PORT(psc, MV88E61XX_PORT_FILTER,
		    MV88E61XX_PORT_FILTER_MAP_DEST |
		    MV88E61XX_PORT_FILTER_DISCARD_TAGGED);
	}
}