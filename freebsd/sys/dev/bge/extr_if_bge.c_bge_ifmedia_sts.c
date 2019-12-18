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
struct bge_softc {int bge_flags; int /*<<< orphan*/  bge_miibus; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int BGE_FLAG_TBI ; 
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int BGE_MACMODE_HALF_DUPLEX ; 
 int BGE_MACSTAT_TBI_PCS_SYNCHED ; 
 int /*<<< orphan*/  BGE_MAC_MODE ; 
 int /*<<< orphan*/  BGE_MAC_STS ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int CSR_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFM_1000_SX ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 int /*<<< orphan*/  IFM_NONE ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 struct bge_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
bge_ifmedia_sts(if_t ifp, struct ifmediareq *ifmr)
{
	struct bge_softc *sc = if_getsoftc(ifp);
	struct mii_data *mii;

	BGE_LOCK(sc);

	if ((if_getflags(ifp) & IFF_UP) == 0) {
		BGE_UNLOCK(sc);
		return;
	}
	if (sc->bge_flags & BGE_FLAG_TBI) {
		ifmr->ifm_status = IFM_AVALID;
		ifmr->ifm_active = IFM_ETHER;
		if (CSR_READ_4(sc, BGE_MAC_STS) &
		    BGE_MACSTAT_TBI_PCS_SYNCHED)
			ifmr->ifm_status |= IFM_ACTIVE;
		else {
			ifmr->ifm_active |= IFM_NONE;
			BGE_UNLOCK(sc);
			return;
		}
		ifmr->ifm_active |= IFM_1000_SX;
		if (CSR_READ_4(sc, BGE_MAC_MODE) & BGE_MACMODE_HALF_DUPLEX)
			ifmr->ifm_active |= IFM_HDX;
		else
			ifmr->ifm_active |= IFM_FDX;
		BGE_UNLOCK(sc);
		return;
	}

	mii = device_get_softc(sc->bge_miibus);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;

	BGE_UNLOCK(sc);
}