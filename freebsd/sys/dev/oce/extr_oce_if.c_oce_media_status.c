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
struct ifnet {int /*<<< orphan*/  if_softc; } ;
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct TYPE_2__ {int link_status; int link_speed; int speed; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10G_SR ; 
 int IFM_10_T ; 
 int IFM_40G_SR4 ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 

__attribute__((used)) static void
oce_media_status(struct ifnet *ifp, struct ifmediareq *req)
{
	POCE_SOFTC sc = (POCE_SOFTC) ifp->if_softc;


	req->ifm_status = IFM_AVALID;
	req->ifm_active = IFM_ETHER;
	
	if (sc->link_status == 1)
		req->ifm_status |= IFM_ACTIVE;
	else 
		return;
	
	switch (sc->link_speed) {
	case 1: /* 10 Mbps */
		req->ifm_active |= IFM_10_T | IFM_FDX;
		sc->speed = 10;
		break;
	case 2: /* 100 Mbps */
		req->ifm_active |= IFM_100_TX | IFM_FDX;
		sc->speed = 100;
		break;
	case 3: /* 1 Gbps */
		req->ifm_active |= IFM_1000_T | IFM_FDX;
		sc->speed = 1000;
		break;
	case 4: /* 10 Gbps */
		req->ifm_active |= IFM_10G_SR | IFM_FDX;
		sc->speed = 10000;
		break;
	case 5: /* 20 Gbps */
		req->ifm_active |= IFM_10G_SR | IFM_FDX;
		sc->speed = 20000;
		break;
	case 6: /* 25 Gbps */
		req->ifm_active |= IFM_10G_SR | IFM_FDX;
		sc->speed = 25000;
		break;
	case 7: /* 40 Gbps */
		req->ifm_active |= IFM_40G_SR4 | IFM_FDX;
		sc->speed = 40000;
		break;
	default:
		sc->speed = 0;
		break;
	}
	
	return;
}