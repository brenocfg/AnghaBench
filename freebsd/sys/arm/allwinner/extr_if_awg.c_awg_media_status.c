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
struct mii_data {int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct awg_softc {int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_LOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  AWG_UNLOCK (struct awg_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 struct awg_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
awg_media_status(if_t ifp, struct ifmediareq *ifmr)
{
	struct awg_softc *sc;
	struct mii_data *mii;

	sc = if_getsoftc(ifp);
	mii = device_get_softc(sc->miibus);

	AWG_LOCK(sc);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	AWG_UNLOCK(sc);
}