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
struct cgem_softc {int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_LOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_UNLOCK (struct cgem_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
cgem_ifmedia_sts(if_t ifp, struct ifmediareq *ifmr)
{
	struct cgem_softc *sc = (struct cgem_softc *) if_getsoftc(ifp);
	struct mii_data *mii;

	mii = device_get_softc(sc->miibus);
	CGEM_LOCK(sc);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	CGEM_UNLOCK(sc);
}