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
struct ifnet {struct dtsec_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct dtsec_softc {TYPE_1__* sc_mii; } ;
struct TYPE_2__ {int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_media_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  DTSEC_UNLOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  mii_pollstat (TYPE_1__*) ; 

__attribute__((used)) static void
dtsec_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct dtsec_softc *sc = ifp->if_softc;

	DTSEC_LOCK(sc);

	mii_pollstat(sc->sc_mii);

	ifmr->ifm_active = sc->sc_mii->mii_media_active;
	ifmr->ifm_status = sc->sc_mii->mii_media_status;

	DTSEC_UNLOCK(sc);
}