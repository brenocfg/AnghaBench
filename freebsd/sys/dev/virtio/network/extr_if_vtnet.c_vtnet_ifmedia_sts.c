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
struct vtnet_softc {int dummy; } ;
struct ifnet {struct vtnet_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_NONE ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_UNLOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_MEDIATYPE ; 
 scalar_t__ vtnet_is_link_up (struct vtnet_softc*) ; 

__attribute__((used)) static void
vtnet_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct vtnet_softc *sc;

	sc = ifp->if_softc;

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	VTNET_CORE_LOCK(sc);
	if (vtnet_is_link_up(sc) != 0) {
		ifmr->ifm_status |= IFM_ACTIVE;
		ifmr->ifm_active |= VTNET_MEDIATYPE;
	} else
		ifmr->ifm_active |= IFM_NONE;
	VTNET_CORE_UNLOCK(sc);
}