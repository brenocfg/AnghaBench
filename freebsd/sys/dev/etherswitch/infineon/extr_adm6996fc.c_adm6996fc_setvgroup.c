#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct adm6996fc_softc {scalar_t__ vlan_mode; } ;
struct TYPE_3__ {int es_vlangroup; int es_member_ports; int es_untagged_ports; int es_vid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ADM6996FC_VF0H ; 
 scalar_t__ ADM6996FC_VF0L ; 
 int ADM6996FC_VV_SHIFT ; 
 int /*<<< orphan*/  ADM6996FC_WRITEREG (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adm6996fc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adm6996fc_setvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct adm6996fc_softc	*sc;
	device_t		 parent;

	sc = device_get_softc(dev);
	parent = device_get_parent(dev);

	if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT) {
		ADM6996FC_WRITEREG(parent, ADM6996FC_VF0L + 2 * vg->es_vlangroup,
		    vg->es_member_ports);
	} else if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		ADM6996FC_WRITEREG(parent, ADM6996FC_VF0L + 2 * vg->es_vlangroup,
		    vg->es_member_ports | ((~vg->es_untagged_ports & 0x3f)<< 6));
		ADM6996FC_WRITEREG(parent, ADM6996FC_VF0H + 2 * vg->es_vlangroup,
		    (1 << ADM6996FC_VV_SHIFT) | vg->es_vid);
	}

	return (0);
}