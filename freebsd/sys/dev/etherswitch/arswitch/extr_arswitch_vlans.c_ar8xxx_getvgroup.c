#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* arswitch_get_dot1q_vlan ) (struct arswitch_softc*,scalar_t__*,scalar_t__*,int) ;int (* arswitch_get_port_vlan ) (struct arswitch_softc*,scalar_t__*,int) ;} ;
struct TYPE_5__ {size_t es_nvlangroups; } ;
struct arswitch_softc {int* vid; int vlan_mode; TYPE_2__ hal; TYPE_1__ info; } ;
struct TYPE_7__ {size_t es_vlangroup; int es_vid; scalar_t__ es_untagged_ports; scalar_t__ es_member_ports; scalar_t__ es_fid; } ;
typedef  TYPE_3__ etherswitch_vlangroup_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARSWITCH_LOCK (struct arswitch_softc*) ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARSWITCH_UNLOCK (struct arswitch_softc*) ; 
 int EINVAL ; 
 int ETHERSWITCH_VID_VALID ; 
#define  ETHERSWITCH_VLAN_DOT1Q 129 
#define  ETHERSWITCH_VLAN_PORT 128 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int stub1 (struct arswitch_softc*,scalar_t__*,scalar_t__*,int) ; 
 int stub2 (struct arswitch_softc*,scalar_t__*,int) ; 

int
ar8xxx_getvgroup(struct arswitch_softc *sc, etherswitch_vlangroup_t *vg)
{
	int err;

	ARSWITCH_LOCK_ASSERT(sc, MA_NOTOWNED);

	if (vg->es_vlangroup > sc->info.es_nvlangroups)
		return (EINVAL);

	/* Reset the members ports. */
	vg->es_untagged_ports = 0;
	vg->es_member_ports = 0;

	/* Not supported. */
	vg->es_fid = 0;

	/* Vlan ID. */
	ARSWITCH_LOCK(sc);
	vg->es_vid = sc->vid[vg->es_vlangroup];
	if ((vg->es_vid & ETHERSWITCH_VID_VALID) == 0) {
		ARSWITCH_UNLOCK(sc);
		return (0);
	}

	/* Member Ports. */
	switch (sc->vlan_mode) {
	case ETHERSWITCH_VLAN_DOT1Q:
		err = sc->hal.arswitch_get_dot1q_vlan(sc, &vg->es_member_ports,
		    &vg->es_untagged_ports,
		    vg->es_vid);
		break;
	case ETHERSWITCH_VLAN_PORT:
		err = sc->hal.arswitch_get_port_vlan(sc, &vg->es_member_ports,
		    vg->es_vid);
		vg->es_untagged_ports = vg->es_member_ports;
		break;
	default:
		vg->es_member_ports = 0;
		vg->es_untagged_ports = 0;
		err = -1;
	}
	ARSWITCH_UNLOCK(sc);

	return (err);
}