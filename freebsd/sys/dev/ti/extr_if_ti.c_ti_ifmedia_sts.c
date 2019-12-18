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
struct ti_softc {scalar_t__ ti_linkstat; scalar_t__ ti_copper; } ;
struct ifnet {struct ti_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ti_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFM_1000_SX ; 
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_100_FX ; 
 int /*<<< orphan*/  IFM_100_TX ; 
 int /*<<< orphan*/  IFM_10_FL ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 scalar_t__ TI_EV_CODE_GIG_LINK_UP ; 
 scalar_t__ TI_EV_CODE_LINK_DOWN ; 
 scalar_t__ TI_EV_CODE_LINK_UP ; 
 int /*<<< orphan*/  TI_GCR_GLINK_STAT ; 
 int /*<<< orphan*/  TI_GCR_LINK_STAT ; 
 int TI_GLNK_FULL_DUPLEX ; 
 int TI_LNK_100MB ; 
 int TI_LNK_10MB ; 
 int TI_LNK_FULL_DUPLEX ; 
 int TI_LNK_HALF_DUPLEX ; 
 int /*<<< orphan*/  TI_LOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_UNLOCK (struct ti_softc*) ; 

__attribute__((used)) static void
ti_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct ti_softc *sc;
	uint32_t media = 0;

	sc = ifp->if_softc;

	TI_LOCK(sc);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (sc->ti_linkstat == TI_EV_CODE_LINK_DOWN) {
		TI_UNLOCK(sc);
		return;
	}

	ifmr->ifm_status |= IFM_ACTIVE;

	if (sc->ti_linkstat == TI_EV_CODE_GIG_LINK_UP) {
		media = CSR_READ_4(sc, TI_GCR_GLINK_STAT);
		if (sc->ti_copper)
			ifmr->ifm_active |= IFM_1000_T;
		else
			ifmr->ifm_active |= IFM_1000_SX;
		if (media & TI_GLNK_FULL_DUPLEX)
			ifmr->ifm_active |= IFM_FDX;
		else
			ifmr->ifm_active |= IFM_HDX;
	} else if (sc->ti_linkstat == TI_EV_CODE_LINK_UP) {
		media = CSR_READ_4(sc, TI_GCR_LINK_STAT);
		if (sc->ti_copper) {
			if (media & TI_LNK_100MB)
				ifmr->ifm_active |= IFM_100_TX;
			if (media & TI_LNK_10MB)
				ifmr->ifm_active |= IFM_10_T;
		} else {
			if (media & TI_LNK_100MB)
				ifmr->ifm_active |= IFM_100_FX;
			if (media & TI_LNK_10MB)
				ifmr->ifm_active |= IFM_10_FL;
		}
		if (media & TI_LNK_FULL_DUPLEX)
			ifmr->ifm_active |= IFM_FDX;
		if (media & TI_LNK_HALF_DUPLEX)
			ifmr->ifm_active |= IFM_HDX;
	}
	TI_UNLOCK(sc);
}