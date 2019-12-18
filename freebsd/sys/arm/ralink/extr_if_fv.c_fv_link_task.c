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
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
struct fv_softc {int fv_link_status; struct ifnet* fv_ifp; int /*<<< orphan*/  fv_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  FV_LOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  FV_UNLOCK (struct fv_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int IFM_ACTIVE ; 
 scalar_t__ IFM_NONE ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fv_link_task(void *arg, int pending)
{
#ifdef MII
	struct fv_softc		*sc;
	struct mii_data		*mii;
	struct ifnet		*ifp;
	/* int			lfdx, mfdx; */

	sc = (struct fv_softc *)arg;

	FV_LOCK(sc);
	mii = device_get_softc(sc->fv_miibus);
	ifp = sc->fv_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		FV_UNLOCK(sc);
		return;
	}

	if (mii->mii_media_status & IFM_ACTIVE) {
		if (IFM_SUBTYPE(mii->mii_media_active) != IFM_NONE)
			sc->fv_link_status = 1;
	} else
		sc->fv_link_status = 0;

	FV_UNLOCK(sc);
#endif
}