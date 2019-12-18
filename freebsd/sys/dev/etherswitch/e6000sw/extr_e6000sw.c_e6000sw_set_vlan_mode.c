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
struct e6000sw_softc {int vlan_mode; int /*<<< orphan*/  num_ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  es_nvlangroups; } ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK_ASSERT (struct e6000sw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E6000SW_NUM_VLANS ; 
 int EINVAL ; 
#define  ETHERSWITCH_VLAN_DOT1Q 129 
#define  ETHERSWITCH_VLAN_PORT 128 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int e6000sw_init_vlan (struct e6000sw_softc*) ; 
 TYPE_1__ etherswitch_info ; 

__attribute__((used)) static int
e6000sw_set_vlan_mode(struct e6000sw_softc *sc, uint32_t mode)
{

	E6000SW_LOCK_ASSERT(sc, SA_XLOCKED);
	switch (mode) {
	case ETHERSWITCH_VLAN_PORT:
		sc->vlan_mode = ETHERSWITCH_VLAN_PORT;
		etherswitch_info.es_nvlangroups = sc->num_ports;
		return (e6000sw_init_vlan(sc));
		break;
	case ETHERSWITCH_VLAN_DOT1Q:
		sc->vlan_mode = ETHERSWITCH_VLAN_DOT1Q;
		etherswitch_info.es_nvlangroups = E6000SW_NUM_VLANS;
		return (e6000sw_init_vlan(sc));
		break;
	default:
		return (EINVAL);
	}
}