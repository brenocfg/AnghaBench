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
struct ifnet {struct gx_softc* if_softc; } ;
struct ifmediareq {int ifm_status; int ifm_active; } ;
struct gx_softc {int dummy; } ;

/* Variables and functions */
 int IFM_1000_T ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_FDX ; 
 int IFT_ETHER ; 

__attribute__((used)) static void
gx_medstat(struct ifnet *ifp, struct ifmediareq *ifm)
{
	struct gx_softc *sc;

	sc = ifp->if_softc;

	/* Lie amazingly.  */
	ifm->ifm_status = IFM_AVALID | IFM_ACTIVE;
	ifm->ifm_active = IFT_ETHER | IFM_1000_T | IFM_FDX;
}