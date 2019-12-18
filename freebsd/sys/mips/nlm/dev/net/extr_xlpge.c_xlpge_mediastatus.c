#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlm_xlpge_softc {scalar_t__ link; scalar_t__ mii_bus; } ;
struct TYPE_4__ {TYPE_1__* ifm_cur; } ;
struct mii_data {TYPE_2__ mii_media; } ;
struct ifnet {struct nlm_xlpge_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 scalar_t__ NLM_LINK_DOWN ; 
 struct mii_data* device_get_softc (scalar_t__) ; 

__attribute__((used)) static void
xlpge_mediastatus(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct nlm_xlpge_softc *sc;
	struct mii_data *md;

	md = NULL;
	sc = ifp->if_softc;

	if (sc->mii_bus)
		md = device_get_softc(sc->mii_bus);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (sc->link == NLM_LINK_DOWN)
		return;

	if (md != NULL)
		ifmr->ifm_active = md->mii_media.ifm_cur->ifm_media;
	ifmr->ifm_status |= IFM_ACTIVE;
}