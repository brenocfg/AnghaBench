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
struct nicvf {int speed; scalar_t__ duplex; scalar_t__ link_up; } ;
struct ifnet {int dummy; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_100_TX ; 
 int /*<<< orphan*/  IFM_10G_SR ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_40G_CR4 ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AUTO ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 int /*<<< orphan*/  NICVF_CORE_LOCK (struct nicvf*) ; 
 int /*<<< orphan*/  NICVF_CORE_UNLOCK (struct nicvf*) ; 
#define  SPEED_10 132 
#define  SPEED_100 131 
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_40000 128 
 struct nicvf* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static void
nicvf_media_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct nicvf *nic = if_getsoftc(ifp);

	NICVF_CORE_LOCK(nic);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (nic->link_up) {
		/* Device attached to working network */
		ifmr->ifm_status |= IFM_ACTIVE;
	}

	switch (nic->speed) {
	case SPEED_10:
		ifmr->ifm_active |= IFM_10_T;
		break;
	case SPEED_100:
		ifmr->ifm_active |= IFM_100_TX;
		break;
	case SPEED_1000:
		ifmr->ifm_active |= IFM_1000_T;
		break;
	case SPEED_10000:
		ifmr->ifm_active |= IFM_10G_SR;
		break;
	case SPEED_40000:
		ifmr->ifm_active |= IFM_40G_CR4;
		break;
	default:
		ifmr->ifm_active |= IFM_AUTO;
		break;
	}

	if (nic->duplex)
		ifmr->ifm_active |= IFM_FDX;
	else
		ifmr->ifm_active |= IFM_HDX;

	NICVF_CORE_UNLOCK(nic);
}