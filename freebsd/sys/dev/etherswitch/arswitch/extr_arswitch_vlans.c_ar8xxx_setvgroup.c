#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* arswitch_purge_dot1q_vlan ) (struct arswitch_softc*,int) ;int (* arswitch_set_dot1q_vlan ) (struct arswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int (* arswitch_set_port_vlan ) (struct arswitch_softc*,int /*<<< orphan*/ ,int) ;} ;
struct arswitch_softc {int vlan_mode; int* vid; TYPE_1__ hal; } ;
struct TYPE_5__ {size_t es_vlangroup; int es_vid; int /*<<< orphan*/  es_member_ports; int /*<<< orphan*/  es_untagged_ports; } ;
typedef  TYPE_2__ etherswitch_vlangroup_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARSWITCH_LOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARSWITCH_UNLOCK (struct arswitch_softc*) ; 
 int EINVAL ; 
 int ETHERSWITCH_VID_MASK ; 
 int ETHERSWITCH_VID_VALID ; 
#define  ETHERSWITCH_VLAN_DOT1Q 129 
#define  ETHERSWITCH_VLAN_PORT 128 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int stub1 (struct arswitch_softc*,int) ; 
 int stub2 (struct arswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct arswitch_softc*,int /*<<< orphan*/ ,int) ; 

int
ar8xxx_setvgroup(struct arswitch_softc *sc, etherswitch_vlangroup_t *vg)
{
	int err, vid;

	ARSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);

	/* Check VLAN mode. */
	if (sc->vlan_mode == 0)
		return (EINVAL);

	/*
	 * Check if we are changing the vlanid for an already used vtu entry.
	 * Then purge the entry first.
	 */
	ARSWITCH_LOCK(sc);
	vid = sc->vid[vg->es_vlangroup];
	if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q &&
	    (vid & ETHERSWITCH_VID_VALID) != 0 &&
	    (vid & ETHERSWITCH_VID_MASK) !=
	    (vg->es_vid & ETHERSWITCH_VID_MASK)) {
		err = sc->hal.arswitch_purge_dot1q_vlan(sc, vid);
		if (err) {
			ARSWITCH_UNLOCK(sc);
			return (err);
		}
	}

	/* Vlan ID. */
	if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		sc->vid[vg->es_vlangroup] = vg->es_vid & ETHERSWITCH_VID_MASK;
		/* Setting the vlanid to zero disables the vlangroup. */
		if (sc->vid[vg->es_vlangroup] == 0) {
			ARSWITCH_UNLOCK(sc);
			return (0);
		}
		sc->vid[vg->es_vlangroup] |= ETHERSWITCH_VID_VALID;
		vid = sc->vid[vg->es_vlangroup];
	}

	/* Member Ports. */
	switch (sc->vlan_mode) {
	case ETHERSWITCH_VLAN_DOT1Q:
		err = sc->hal.arswitch_set_dot1q_vlan(sc, vg->es_member_ports,
		    vg->es_untagged_ports, vid);
		break;
	case ETHERSWITCH_VLAN_PORT:
		err = sc->hal.arswitch_set_port_vlan(sc, vg->es_member_ports, vid);
		break;
	default:
		err = -1;
	}
	ARSWITCH_UNLOCK(sc);
	return (err);
}