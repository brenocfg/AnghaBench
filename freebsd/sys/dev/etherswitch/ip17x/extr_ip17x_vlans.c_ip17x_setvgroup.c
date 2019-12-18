#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int (* ip17x_hw_setup ) (struct ip17x_softc*) ;} ;
struct TYPE_6__ {int es_nvlangroups; } ;
struct ip17x_softc {scalar_t__ vlan_mode; int numports; int* portphy; TYPE_3__ hal; TYPE_2__* vlan; TYPE_1__ info; } ;
struct TYPE_9__ {int es_vid; int es_vlangroup; int es_member_ports; } ;
typedef  TYPE_4__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {int vlanid; int ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETHERSWITCH_VID_MASK ; 
 int ETHERSWITCH_VID_VALID ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 int /*<<< orphan*/  IP175C ; 
 int IP175C_LAST_VLAN ; 
 scalar_t__ IP17X_IS_SWITCH (struct ip17x_softc*,int /*<<< orphan*/ ) ; 
 struct ip17x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (struct ip17x_softc*) ; 
 int stub2 (struct ip17x_softc*) ; 

int
ip17x_setvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct ip17x_softc *sc;
	uint32_t phy;
	int i;

	sc = device_get_softc(dev);

	/* Check VLAN mode. */
	if (sc->vlan_mode == 0)
		return (EINVAL);

	/* IP175C don't support VLAN IDs > 15. */
	if (IP17X_IS_SWITCH(sc, IP175C) &&
	    (vg->es_vid & ETHERSWITCH_VID_MASK) > IP175C_LAST_VLAN)
		return (EINVAL);

	/* Vlan ID. */
	if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		for (i = 0; i < sc->info.es_nvlangroups; i++) {
			/* Is this Vlan ID already set in another vlangroup ? */
			if (i != vg->es_vlangroup &&
			    sc->vlan[i].vlanid & ETHERSWITCH_VID_VALID &&
			    (sc->vlan[i].vlanid & ETHERSWITCH_VID_MASK) ==
			    (vg->es_vid & ETHERSWITCH_VID_MASK))
				return (EINVAL);
		}
		sc->vlan[vg->es_vlangroup].vlanid = vg->es_vid &
		    ETHERSWITCH_VID_MASK;
		/* Setting the vlanid to zero disables the vlangroup. */
		if (sc->vlan[vg->es_vlangroup].vlanid == 0) {
			sc->vlan[vg->es_vlangroup].ports = 0;
			return (sc->hal.ip17x_hw_setup(sc));
		}
		sc->vlan[vg->es_vlangroup].vlanid |= ETHERSWITCH_VID_VALID;
	}

	/* Member Ports. */
	sc->vlan[vg->es_vlangroup].ports = 0;
	for (i = 0; i < sc->numports; i++) {
		if ((vg->es_member_ports & (1 << i)) == 0)
			continue;
		phy = sc->portphy[i];
		sc->vlan[vg->es_vlangroup].ports |= (1 << phy);
	}

	return (sc->hal.ip17x_hw_setup(sc));
}