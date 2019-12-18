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
 int /*<<< orphan*/  ip175d_hw_setup (struct ip17x_softc*) ; 
 int /*<<< orphan*/  ip17x_reset_vlans (struct ip17x_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ip17x_updatephy (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int
ip175d_set_vlan_mode(struct ip17x_softc *sc, uint32_t mode)
{

	switch (mode) {
	case ETHERSWITCH_VLAN_DOT1Q:
		/*
		 * VLAN classification rules: tag-based VLANs,
		 * use VID to classify, drop packets that cannot
		 * be classified.
		 */
		ip17x_updatephy(sc->sc_dev, 22, 0, 0x3fff, 0x003f);
		sc->vlan_mode = mode;
		break;
	case ETHERSWITCH_VLAN_PORT:
		sc->vlan_mode = mode;
		/* fallthrough */
	default:
		/*
		 * VLAN classification rules: everything off &
		 * clear table.
		 */
		ip17x_updatephy(sc->sc_dev, 22, 0, 0xbfff, 0x8000);
		sc->vlan_mode = 0;
		break;
	}

	if (sc->vlan_mode != 0) {
		/*
		 * Ingress rules: CFI=1 dropped, null VID is untagged, VID=1 passed,
		 * VID=0xfff discarded, admin both tagged and untagged, ingress
		 * filters enabled.
		 */
		ip17x_updatephy(sc->sc_dev, 22, 1, 0x0fff, 0x0c3f);

		/* Egress rules: IGMP processing off, keep VLAN header off. */
		ip17x_updatephy(sc->sc_dev, 22, 2, 0x0fff, 0x0000);
	} else {
		ip17x_updatephy(sc->sc_dev, 22, 1, 0x0fff, 0x043f);
		ip17x_updatephy(sc->sc_dev, 22, 2, 0x0fff, 0x0020);
	}

	/* Reset vlans. */
	ip17x_reset_vlans(sc, sc->vlan_mode);

	/* Update switch configuration. */
	ip175d_hw_setup(sc);

	return (0);
}