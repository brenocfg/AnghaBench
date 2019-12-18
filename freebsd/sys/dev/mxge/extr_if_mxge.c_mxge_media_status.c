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
struct ifnet {TYPE_1__* if_softc; } ;
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct TYPE_2__ {int current_media; scalar_t__ link_state; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 

__attribute__((used)) static void
mxge_media_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	mxge_softc_t *sc = ifp->if_softc;
	

	if (sc == NULL)
		return;
	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER | IFM_FDX;
	ifmr->ifm_status |= sc->link_state ? IFM_ACTIVE : 0;
	ifmr->ifm_active |= sc->current_media;
}