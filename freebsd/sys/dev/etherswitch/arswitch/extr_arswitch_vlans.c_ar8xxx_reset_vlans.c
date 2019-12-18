#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* arswitch_set_dot1q_vlan ) (struct arswitch_softc*,int,int,int) ;int /*<<< orphan*/  (* arswitch_vlan_set_pvid ) (struct arswitch_softc*,int,int) ;scalar_t__ (* arswitch_flush_dot1q_vlan ) (struct arswitch_softc*) ;} ;
struct arswitch_softc {int* vid; int numphys; scalar_t__ vlan_mode; int /*<<< orphan*/  sc_dev; TYPE_1__ hal; } ;

/* Variables and functions */
 int AR8X16_PORT_CTRL_DOUBLE_TAG ; 
 int AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_SHIFT ; 
 int AR8X16_PORT_VLAN_DEST_PORTS_SHIFT ; 
 int AR8X16_PORT_VLAN_MODE_MASK ; 
 int AR8X16_PORT_VLAN_MODE_PORT_ONLY ; 
 int AR8X16_PORT_VLAN_MODE_SECURE ; 
 int AR8X16_PORT_VLAN_MODE_SHIFT ; 
 int /*<<< orphan*/  AR8X16_REG_PORT_CTRL (int) ; 
 int /*<<< orphan*/  AR8X16_REG_PORT_VLAN (int) ; 
 int AR8X16_VLAN_MEMBER ; 
 int /*<<< orphan*/  ARSWITCH_LOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARSWITCH_UNLOCK (struct arswitch_softc*) ; 
 int ETHERSWITCH_VID_VALID ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 scalar_t__ arswitch_modifyreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct arswitch_softc*) ; 
 int /*<<< orphan*/  stub2 (struct arswitch_softc*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct arswitch_softc*,int,int,int) ; 

void
ar8xxx_reset_vlans(struct arswitch_softc *sc)
{
	uint32_t ports;
	int i, j;

	ARSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);

	ARSWITCH_LOCK(sc);

	/* Reset all vlan data. */
	memset(sc->vid, 0, sizeof(sc->vid));

	/* Disable the QinQ and egress filters for all ports. */
	for (i = 0; i <= sc->numphys; i++) {
		if (arswitch_modifyreg(sc->sc_dev, AR8X16_REG_PORT_CTRL(i),
		    0x3 << AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_SHIFT |
		    AR8X16_PORT_CTRL_DOUBLE_TAG, 0)) {
			ARSWITCH_UNLOCK(sc);
			return;
		}
	}

	if (sc->hal.arswitch_flush_dot1q_vlan(sc)) {
		ARSWITCH_UNLOCK(sc);
		return;
	}

	if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		/*
		 * Reset the port based vlan settings and turn on the
		 * ingress filter for all ports.
		 */
		ports = 0;
		for (i = 0; i <= sc->numphys; i++)
			arswitch_modifyreg(sc->sc_dev,
			    AR8X16_REG_PORT_VLAN(i),
			    AR8X16_PORT_VLAN_MODE_MASK |
			    AR8X16_VLAN_MEMBER <<
			    AR8X16_PORT_VLAN_DEST_PORTS_SHIFT,
			    AR8X16_PORT_VLAN_MODE_SECURE <<
			    AR8X16_PORT_VLAN_MODE_SHIFT);

		/*
		 * Setup vlan 1 as PVID for all switch ports.  Add all ports
		 * as members of vlan 1.
		 */
		sc->vid[0] = 1;
		/* Set PVID for everyone. */
		for (i = 0; i <= sc->numphys; i++)
			sc->hal.arswitch_vlan_set_pvid(sc, i, sc->vid[0]);
		ports = 0;
		for (i = 0; i <= sc->numphys; i++)
			ports |= (1 << i);
		sc->hal.arswitch_set_dot1q_vlan(sc, ports, sc->vid[0], sc->vid[0]);
		sc->vid[0] |= ETHERSWITCH_VID_VALID;
	} else if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT) {
		/* Initialize the port based vlans. */
		for (i = 0; i <= sc->numphys; i++) {
			sc->vid[i] = i | ETHERSWITCH_VID_VALID;
			ports = 0;
			for (j = 0; j <= sc->numphys; j++)
				ports |= (1 << j);
			arswitch_modifyreg(sc->sc_dev,
			    AR8X16_REG_PORT_VLAN(i),
			    AR8X16_PORT_VLAN_MODE_MASK |
			    AR8X16_VLAN_MEMBER <<
			    AR8X16_PORT_VLAN_DEST_PORTS_SHIFT,
			    ports << AR8X16_PORT_VLAN_DEST_PORTS_SHIFT |
			    AR8X16_PORT_VLAN_MODE_SECURE <<
			    AR8X16_PORT_VLAN_MODE_PORT_ONLY);
			    /* XXX TODO: SECURE / PORT_ONLY is wrong? */
		}
	} else {
		/* Disable the ingress filter and get everyone on all vlans. */
		for (i = 0; i <= sc->numphys; i++)
			arswitch_modifyreg(sc->sc_dev,
			    AR8X16_REG_PORT_VLAN(i),
			    AR8X16_PORT_VLAN_MODE_MASK |
			    AR8X16_VLAN_MEMBER <<
			    AR8X16_PORT_VLAN_DEST_PORTS_SHIFT,
			    AR8X16_VLAN_MEMBER <<
			    AR8X16_PORT_VLAN_DEST_PORTS_SHIFT |
			    AR8X16_PORT_VLAN_MODE_SECURE <<
			    AR8X16_PORT_VLAN_MODE_PORT_ONLY);
	}
	ARSWITCH_UNLOCK(sc);
}