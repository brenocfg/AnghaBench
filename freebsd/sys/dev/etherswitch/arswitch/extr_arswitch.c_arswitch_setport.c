#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ifmedia {int dummy; } ;
struct mii_data {struct ifmedia mii_media; } ;
struct ifnet {int dummy; } ;
struct TYPE_7__ {int (* arswitch_port_vlan_setup ) (struct arswitch_softc*,TYPE_3__*) ;} ;
struct TYPE_6__ {scalar_t__ es_nports; } ;
struct arswitch_softc {scalar_t__ vlan_mode; TYPE_2__ hal; TYPE_1__ info; } ;
struct TYPE_8__ {scalar_t__ es_port; int /*<<< orphan*/  es_ifr; int /*<<< orphan*/ * es_led; } ;
typedef  TYPE_3__ etherswitch_port_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327 ; 
 scalar_t__ AR8X16_IS_SWITCH (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 int /*<<< orphan*/  SIOCSIFMEDIA ; 
 struct ifnet* arswitch_ifpforport (struct arswitch_softc*,scalar_t__) ; 
 scalar_t__ arswitch_is_cpuport (struct arswitch_softc*,scalar_t__) ; 
 struct mii_data* arswitch_miiforport (struct arswitch_softc*,scalar_t__) ; 
 int arswitch_setled (struct arswitch_softc*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (struct ifnet*,int /*<<< orphan*/ *,struct ifmedia*,int /*<<< orphan*/ ) ; 
 int stub1 (struct arswitch_softc*,TYPE_3__*) ; 

__attribute__((used)) static int
arswitch_setport(device_t dev, etherswitch_port_t *p)
{
	int err, i;
	struct arswitch_softc *sc;
	struct ifmedia *ifm;
	struct mii_data *mii;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	if (p->es_port < 0 || p->es_port > sc->info.es_nports)
		return (ENXIO);

	/* Port flags. */
	if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		err = sc->hal.arswitch_port_vlan_setup(sc, p);
		if (err)
			return (err);
	}

	/* Do not allow media or led changes on CPU port. */
	if (arswitch_is_cpuport(sc, p->es_port))
		return (0);
	
	if (AR8X16_IS_SWITCH(sc, AR8327))
	{
		for (i = 0; i < 3; i++)
		{	
			int err;
			err = arswitch_setled(sc, p->es_port-1, i, p->es_led[i]);
			if (err)
				return (err);
		}
	}

	mii = arswitch_miiforport(sc, p->es_port);
	if (mii == NULL)
		return (ENXIO);

	ifp = arswitch_ifpforport(sc, p->es_port);

	ifm = &mii->mii_media;
	return (ifmedia_ioctl(ifp, &p->es_ifr, ifm, SIOCSIFMEDIA));
}