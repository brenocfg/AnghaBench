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
struct ifnet {int /*<<< orphan*/  if_softc; } ;
struct ifmediareq {int ifm_active; int ifm_status; } ;
struct ifmedia {TYPE_1__* ifm_cur; } ;
typedef  TYPE_2__* priv_p ;
struct TYPE_4__ {int link_status; struct ifmedia media; } ;
struct TYPE_3__ {int ifm_media; } ;

/* Variables and functions */
 int IFM_1000_T ; 
 int IFM_ACTIVE ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 

__attribute__((used)) static void
ng_eiface_mediastatus(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	const priv_p priv = (priv_p)ifp->if_softc;
	struct ifmedia *ifm = &priv->media;

	if (ifm->ifm_cur->ifm_media == (IFM_ETHER | IFM_AUTO) &&
	    (priv->link_status & IFM_ACTIVE))
		ifmr->ifm_active = IFM_ETHER | IFM_1000_T | IFM_FDX;
	else
		ifmr->ifm_active = ifm->ifm_cur->ifm_media;
	ifmr->ifm_status = priv->link_status;

	return;
}