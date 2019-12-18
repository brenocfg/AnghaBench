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
struct e6060sw_softc {scalar_t__ vlan_mode; int smi_offset; } ;
struct TYPE_3__ {int es_vid; int es_vlangroup; int es_member_ports; int es_untagged_ports; scalar_t__ es_fid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CORE_REGISTER ; 
 void* ETHERSWITCH_VID_VALID ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int MDIO_READREG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_VLAN_MAP ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct e6060sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int e6060sw_read_vtu (int /*<<< orphan*/ ,scalar_t__,int*,int*) ; 

__attribute__((used)) static int
e6060sw_getvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	struct e6060sw_softc *sc;
	int data1, data2;
	int vid;
	int i, tag;

	sc = device_get_softc(dev);

	if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT) {
		vg->es_vid = ETHERSWITCH_VID_VALID;
		vg->es_vid |= vg->es_vlangroup;
		data1 = MDIO_READREG(device_get_parent(dev), 
		    CORE_REGISTER + sc->smi_offset + vg->es_vlangroup,
		    PORT_VLAN_MAP);
		vg->es_member_ports = data1 & 0x3f;
		vg->es_untagged_ports = vg->es_member_ports;
		vg->es_fid = 0;
	} else if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		if (vg->es_vlangroup == 0)
			return (0);
		vid = e6060sw_read_vtu(dev, vg->es_vlangroup, &data1, &data2);
		if (vid > 0) {
			vg->es_vid = ETHERSWITCH_VID_VALID;
			vg->es_vid |= vid;
			vg->es_member_ports = 0;
			vg->es_untagged_ports = 0;
			for (i = 0; i < 4; ++i) {
				tag = data1 >> (i * 4) & 3;
				if (tag == 0 || tag == 1) {
					vg->es_member_ports |= 1 << i;
					vg->es_untagged_ports |= 1 << i;
				} else if (tag == 2) {
					vg->es_member_ports |= 1 << i;
				}
			}
			for (i = 0; i < 2; ++i) {
				tag = data2 >> (i * 4) & 3;
				if (tag == 0 || tag == 1) {
					vg->es_member_ports |= 1 << (i + 4);
					vg->es_untagged_ports |= 1 << (i + 4);
				} else if (tag == 2) {
					vg->es_member_ports |= 1 << (i + 4);
				}
			}

		}
	} else {
		vg->es_vid = 0;
	}
	return (0);
}