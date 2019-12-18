#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int es_vlangroup; int es_vid; int /*<<< orphan*/  es_untagged_ports; int /*<<< orphan*/  es_member_ports; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
struct TYPE_7__ {int num_ports; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ e6000sw_softc_t ;

/* Variables and functions */
 int EINVAL ; 
 int ETHERSWITCH_VID_VALID ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  e6000sw_port_vlan_assign (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e6000sw_set_port_vlan(e6000sw_softc_t *sc, etherswitch_vlangroup_t *vg)
{
	uint32_t port;

	port = vg->es_vlangroup;
	if (port > sc->num_ports)
		return (EINVAL);

	if (vg->es_member_ports != vg->es_untagged_ports) {
		device_printf(sc->dev, "Tagged ports not supported.\n");
		return (EINVAL);
	}

	e6000sw_port_vlan_assign(sc, port, 0, vg->es_untagged_ports);
	vg->es_vid = port | ETHERSWITCH_VID_VALID;

	return (0);
}