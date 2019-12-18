#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  etherswitch_vlangroup_t ;
struct TYPE_6__ {scalar_t__ vlan_mode; } ;
typedef  TYPE_1__ e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int e6000sw_set_dot1q_vlan (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int e6000sw_set_port_vlan (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
e6000sw_setvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{
	e6000sw_softc_t *sc;

	sc = device_get_softc(dev);
	E6000SW_LOCK_ASSERT(sc, SA_XLOCKED);

	if (sc->vlan_mode == ETHERSWITCH_VLAN_PORT)
		return (e6000sw_set_port_vlan(sc, vg));
	else if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q)
		return (e6000sw_set_dot1q_vlan(sc, vg));

	return (EINVAL);
}