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
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct my_softc {struct ifmedia ifmedia; } ;
struct ifnet {struct my_softc* if_softc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IFM_AUTO ; 
 scalar_t__ IFM_ETHER ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MY_FLAG_SCHEDDELAY ; 
 int /*<<< orphan*/  MY_LOCK (struct my_softc*) ; 
 int /*<<< orphan*/  MY_UNLOCK (struct my_softc*) ; 
 int /*<<< orphan*/  my_autoneg_mii (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_setmode_mii (struct my_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
my_ifmedia_upd(struct ifnet * ifp)
{
	struct my_softc *sc;
	struct ifmedia *ifm;

	sc = ifp->if_softc;
	MY_LOCK(sc);
	ifm = &sc->ifmedia;
	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER) {
		MY_UNLOCK(sc);
		return (EINVAL);
	}
	if (IFM_SUBTYPE(ifm->ifm_media) == IFM_AUTO)
		my_autoneg_mii(sc, MY_FLAG_SCHEDDELAY, 1);
	else
		my_setmode_mii(sc, ifm->ifm_media);
	MY_UNLOCK(sc);
	return (0);
}