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
typedef  int uint32_t ;
struct ip17x_softc {int phymask; int* phyport; TYPE_1__* vlan; } ;
struct TYPE_5__ {size_t es_vlangroup; int es_member_ports; int es_untagged_ports; scalar_t__ es_fid; int /*<<< orphan*/  es_vid; } ;
typedef  TYPE_2__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int ports; int /*<<< orphan*/  vlanid; } ;

/* Variables and functions */
 int MII_NPHY ; 
 struct ip17x_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
ip17x_getvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct ip17x_softc *sc;
	uint32_t port;
	int i;

	sc = device_get_softc(dev);

	/* Vlan ID. */
	vg->es_vid = sc->vlan[vg->es_vlangroup].vlanid;

	/* Member Ports. */
	vg->es_member_ports = 0;
	for (i = 0; i < MII_NPHY; i++) {
		if ((sc->phymask & (1 << i)) == 0)
			continue;
		if ((sc->vlan[vg->es_vlangroup].ports & (1 << i)) == 0)
			continue;
		port = sc->phyport[i];
		vg->es_member_ports |= (1 << port);
	}

	/* Not supported. */
	vg->es_untagged_ports = vg->es_member_ports;
	vg->es_fid = 0;

	return (0);
}