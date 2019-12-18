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
struct ip17x_vlan {int vlanid; int ports; } ;
struct ip17x_softc {scalar_t__ vlan_mode; int addtag; int striptag; int numports; int* pvid; int /*<<< orphan*/  sc_dev; struct ip17x_vlan* vlan; } ;

/* Variables and functions */
 int ETHERSWITCH_VID_MASK ; 
 int ETHERSWITCH_VID_VALID ; 
 int IP17X_MAX_VLANS ; 
 int MII_NPHY ; 
 int /*<<< orphan*/  ip17x_writephy (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
ip175d_hw_setup(struct ip17x_softc *sc)
{
	struct ip17x_vlan *v;
	uint32_t ports[IP17X_MAX_VLANS];
	uint32_t addtag[IP17X_MAX_VLANS];
	uint32_t striptag[IP17X_MAX_VLANS];
	uint32_t vlan_mask;
	int i, j;

	vlan_mask = 0;
	for (i = 0; i < IP17X_MAX_VLANS; i++) {

		ports[i] = 0;
		addtag[i] = 0;
		striptag[i] = 0;

		v = &sc->vlan[i];
		if ((v->vlanid & ETHERSWITCH_VID_VALID) == 0 ||
		    sc->vlan_mode == 0) {
			/* Vlangroup disabled.  Reset the filter. */
			ip17x_writephy(sc->sc_dev, 22, 14 + i, i + 1);
			ports[i] = 0x3f;
			continue;
		}

		vlan_mask |= (1 << i);
		ports[i] = v->ports;

		/* Setup the filter, write the VLAN id. */
		ip17x_writephy(sc->sc_dev, 22, 14 + i,
		    v->vlanid & ETHERSWITCH_VID_MASK);

		for (j = 0; j < MII_NPHY; j++) {
			if ((ports[i] & (1 << j)) == 0)
				continue;
			if (sc->addtag & (1 << j))
				addtag[i] |= (1 << j);
			if (sc->striptag & (1 << j))
				striptag[i] |= (1 << j);
		}
	}

	/* Write the port masks, tag adds and removals. */
	for (i = 0; i < IP17X_MAX_VLANS / 2; i++) {
		ip17x_writephy(sc->sc_dev, 23, i,
		    ports[2 * i] | (ports[2 * i + 1] << 8));
		ip17x_writephy(sc->sc_dev, 23, i + 8,
		    addtag[2 * i] | (addtag[2 * i + 1] << 8));
		ip17x_writephy(sc->sc_dev, 23, i + 16,
		    striptag[2 * i] | (striptag[2 * i + 1] << 8));
	}

	/* Write the in use vlan mask. */
	ip17x_writephy(sc->sc_dev, 22, 10, vlan_mask);

	/* Write the PVID of each port. */
	for (i = 0; i < sc->numports; i++)
		ip17x_writephy(sc->sc_dev, 22, 4 + i, sc->pvid[i]);

	return (0);
}