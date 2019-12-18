#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ip17x_softc {int vlan_mode; } ;

/* Variables and functions */
#define  ETHERSWITCH_VLAN_DOT1Q 129 
#define  ETHERSWITCH_VLAN_PORT 128 
 int ip175c_dot1q_vlan_setup (struct ip17x_softc*) ; 
 int ip175c_port_vlan_setup (struct ip17x_softc*) ; 

__attribute__((used)) static int
ip175c_hw_setup(struct ip17x_softc *sc)
{

	switch (sc->vlan_mode) {
	case ETHERSWITCH_VLAN_PORT:
		return (ip175c_port_vlan_setup(sc));
		break;
	case ETHERSWITCH_VLAN_DOT1Q:
		return (ip175c_dot1q_vlan_setup(sc));
		break;
	}
	return (-1);
}