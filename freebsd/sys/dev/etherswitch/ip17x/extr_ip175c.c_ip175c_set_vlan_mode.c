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
typedef  int uint32_t ;
struct ip17x_softc {int vlan_mode; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
#define  ETHERSWITCH_VLAN_DOT1Q 129 
#define  ETHERSWITCH_VLAN_PORT 128 
 int /*<<< orphan*/  ip175c_hw_setup (struct ip17x_softc*) ; 
 int /*<<< orphan*/  ip17x_reset_vlans (struct ip17x_softc*,int) ; 
 int /*<<< orphan*/  ip17x_updatephy (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int
ip175c_set_vlan_mode(struct ip17x_softc *sc, uint32_t mode)
{

	switch (mode) {
	case ETHERSWITCH_VLAN_DOT1Q:
		/* Enable VLAN tag processing. */
		ip17x_updatephy(sc->sc_dev, 30, 9, 0x80, 0x80);
		sc->vlan_mode = mode;
		break;
	case ETHERSWITCH_VLAN_PORT:
	default:
		/* Disable VLAN tag processing. */
		ip17x_updatephy(sc->sc_dev, 30, 9, 0x80, 0);
		sc->vlan_mode = ETHERSWITCH_VLAN_PORT;
		break;
	}

	/* Reset vlans. */
	ip17x_reset_vlans(sc, sc->vlan_mode);

	/* Update switch configuration. */
	ip175c_hw_setup(sc);

	return (0);
}