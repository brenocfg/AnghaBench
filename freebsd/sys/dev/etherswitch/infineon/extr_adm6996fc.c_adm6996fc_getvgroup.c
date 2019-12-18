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
struct TYPE_3__ {int es_vlangroup; int es_vid; int es_member_ports; int es_untagged_ports; scalar_t__ es_fid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ADM6996FC_READREG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ADM6996FC_VF0H ; 
 scalar_t__ ADM6996FC_VF0L ; 
 int ADM6996FC_VV_SHIFT ; 
 void* ETHERSWITCH_VID_VALID ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adm6996fc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adm6996fc_getvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct adm6996fc_softc	*sc;
	device_t		 parent;
	int			 datahi, datalo;

	sc = device_get_softc(dev);
	parent = device_get_parent(dev);

	if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT) {
		if (vg->es_vlangroup <= 5) {
			vg->es_vid = ETHERSWITCH_VID_VALID;
			vg->es_vid |= vg->es_vlangroup;
			datalo = ADM6996FC_READREG(parent,
			    ADM6996FC_VF0L + 2 * vg->es_vlangroup);
			datahi = ADM6996FC_READREG(parent,
			    ADM6996FC_VF0H + 2 * vg->es_vlangroup);

			vg->es_member_ports = datalo & 0x3f;
			vg->es_untagged_ports = vg->es_member_ports;
			vg->es_fid = 0;
		} else {
			vg->es_vid = 0;
		}
	} else if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		datalo = ADM6996FC_READREG(parent,
		    ADM6996FC_VF0L + 2 * vg->es_vlangroup);
		datahi = ADM6996FC_READREG(parent,
		    ADM6996FC_VF0H + 2 * vg->es_vlangroup);
		
		if (datahi & (1 << ADM6996FC_VV_SHIFT)) {
			vg->es_vid = ETHERSWITCH_VID_VALID;
			vg->es_vid |= datahi & 0xfff;
			vg->es_member_ports = datalo & 0x3f;
			vg->es_untagged_ports = (~datalo >> 6) & 0x3f;
			vg->es_fid = 0;
		} else {
			vg->es_fid = 0;
		}
	} else {
		vg->es_fid = 0;
	}

	return (0);
}