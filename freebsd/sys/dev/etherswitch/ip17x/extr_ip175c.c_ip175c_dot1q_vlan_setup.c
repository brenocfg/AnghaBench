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
typedef  int /*<<< orphan*/  vlans ;
typedef  int uint32_t ;
struct ip17x_vlan {int vlanid; int ports; } ;
struct ip17x_softc {int cpuport; int numports; int addtag; int striptag; int* pvid; int /*<<< orphan*/  sc_dev; struct ip17x_vlan* vlan; } ;

/* Variables and functions */
 size_t ETHERSWITCH_VID_MASK ; 
 int ETHERSWITCH_VID_VALID ; 
 int IP175X_CPU_PORT ; 
 int IP17X_MAX_VLANS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ ip17x_updatephy (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ip17x_writephy (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ip175c_dot1q_vlan_setup(struct ip17x_softc *sc)
{
	struct ip17x_vlan *v;
	uint32_t data;
	uint32_t vlans[IP17X_MAX_VLANS];
	int i, j;

	KASSERT(sc->cpuport == 5, ("cpuport != 5 not supported for IP175C"));
	KASSERT(sc->numports == 6, ("numports != 6 not supported for IP175C"));

	/* Add and strip VLAN tags. */
	data = (sc->addtag & ~(1 << IP175X_CPU_PORT)) << 11;
	data |= (sc->striptag & ~(1 << IP175X_CPU_PORT)) << 6;
	if (sc->addtag & (1 << IP175X_CPU_PORT))
		data |= (1 << 1);
	if (sc->striptag & (1 << IP175X_CPU_PORT))
		data |= (1 << 0);
	if (ip17x_writephy(sc->sc_dev, 29, 23, data))
		return (-1);

	/* Set the VID_IDX_SEL to 0. */
	if (ip17x_updatephy(sc->sc_dev, 30, 9, 0x70, 0))
		return (-1);

	/* Calculate the port masks. */
	memset(vlans, 0, sizeof(vlans));
	for (i = 0; i < IP17X_MAX_VLANS; i++) {
		v = &sc->vlan[i];
		if ((v->vlanid & ETHERSWITCH_VID_VALID) == 0)
			continue;
		vlans[v->vlanid & ETHERSWITCH_VID_MASK] = v->ports;
	}

	for (j = 0, i = 1; i <= IP17X_MAX_VLANS / 2; i++) {
		data = vlans[j++] & 0x3f;
		data |= (vlans[j++] & 0x3f) << 8;
		if (ip17x_writephy(sc->sc_dev, 30, i, data))
			return (-1);
	}

	/* Port default VLAN ID. */
	for (i = 0; i < sc->numports; i++) {
		if (i == IP175X_CPU_PORT) {
			if (ip17x_writephy(sc->sc_dev, 29, 30, sc->pvid[i]))
				return (-1);
		} else {
			if (ip17x_writephy(sc->sc_dev, 29, 24 + i, sc->pvid[i]))
				return (-1);
		}
	}

	return (0);
}