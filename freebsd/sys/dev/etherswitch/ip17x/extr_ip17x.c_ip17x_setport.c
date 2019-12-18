#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ifmedia {int dummy; } ;
struct mii_data {struct ifmedia mii_media; } ;
struct TYPE_5__ {scalar_t__ (* ip17x_hw_setup ) (struct ip17x_softc*) ;} ;
struct ip17x_softc {size_t numports; int* portphy; scalar_t__ vlan_mode; scalar_t__* pvid; int addtag; int striptag; int cpuport; TYPE_1__ hal; } ;
struct ifnet {int dummy; } ;
struct TYPE_6__ {scalar_t__ ifm_count; } ;
struct TYPE_7__ {size_t es_port; scalar_t__ es_pvid; int es_flags; int /*<<< orphan*/  es_ifr; TYPE_2__ es_ifmr; } ;
typedef  TYPE_3__ etherswitch_port_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int ETHERSWITCH_PORT_ADDTAG ; 
 int ETHERSWITCH_PORT_STRIPTAG ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 int /*<<< orphan*/  IP175C ; 
 scalar_t__ IP175C_LAST_VLAN ; 
 scalar_t__ IP17X_IS_SWITCH (struct ip17x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIOCSIFMEDIA ; 
 struct ip17x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (struct ifnet*,int /*<<< orphan*/ *,struct ifmedia*,int /*<<< orphan*/ ) ; 
 struct ifnet* ip17x_ifpforport (struct ip17x_softc*,size_t) ; 
 struct mii_data* ip17x_miiforport (struct ip17x_softc*,size_t) ; 
 scalar_t__ stub1 (struct ip17x_softc*) ; 

__attribute__((used)) static int
ip17x_setport(device_t dev, etherswitch_port_t *p)
{
	struct ip17x_softc *sc;
	struct ifmedia *ifm;
	struct ifnet *ifp;
	struct mii_data *mii;
	int phy;

 	sc = device_get_softc(dev);
	if (p->es_port < 0 || p->es_port >= sc->numports)
		return (ENXIO);

	phy = sc->portphy[p->es_port];
	ifp = ip17x_ifpforport(sc, p->es_port);
	mii = ip17x_miiforport(sc, p->es_port);
	if (ifp == NULL || mii == NULL)
		return (ENXIO);

	/* Port flags. */
	if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {

		/* Set the PVID. */
		if (p->es_pvid != 0) {
			if (IP17X_IS_SWITCH(sc, IP175C) &&
			    p->es_pvid > IP175C_LAST_VLAN)
				return (ENXIO);
			sc->pvid[phy] = p->es_pvid;
		}

		/* Mutually exclusive. */
		if (p->es_flags & ETHERSWITCH_PORT_ADDTAG &&
		    p->es_flags & ETHERSWITCH_PORT_STRIPTAG)
			return (EINVAL);

		/* Reset the settings for this port. */
		sc->addtag &= ~(1 << phy);
		sc->striptag &= ~(1 << phy);

		/* And then set it to the new value. */
		if (p->es_flags & ETHERSWITCH_PORT_ADDTAG)
			sc->addtag |= (1 << phy);
		if (p->es_flags & ETHERSWITCH_PORT_STRIPTAG)
			sc->striptag |= (1 << phy);
	}

	/* Update the switch configuration. */
	if (sc->hal.ip17x_hw_setup(sc))
		return (ENXIO);

	/* Do not allow media changes on CPU port. */
	if (phy == sc->cpuport)
		return (0);

	/* No media settings ? */
	if (p->es_ifmr.ifm_count == 0)
		return (0);

	ifm = &mii->mii_media;
	return (ifmedia_ioctl(ifp, &p->es_ifr, ifm, SIOCSIFMEDIA));
}