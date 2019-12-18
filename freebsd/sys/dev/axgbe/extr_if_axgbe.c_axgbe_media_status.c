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
struct ifnet {struct axgbe_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct TYPE_3__ {scalar_t__ duplex; int speed; int /*<<< orphan*/  link; } ;
struct TYPE_4__ {TYPE_1__ phy; } ;
struct axgbe_softc {TYPE_2__ prv; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  IFM_1000_KX ; 
 int /*<<< orphan*/  IFM_10G_KR ; 
 int /*<<< orphan*/  IFM_2500_KX ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_2500 128 

__attribute__((used)) static void
axgbe_media_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct axgbe_softc *sc;

	sc = ifp->if_softc;

	ifmr->ifm_status = IFM_AVALID;
	if (!sc->prv.phy.link)
		return;

	ifmr->ifm_status |= IFM_ACTIVE;
	ifmr->ifm_active = IFM_ETHER;

	if (sc->prv.phy.duplex == DUPLEX_FULL)
		ifmr->ifm_active |= IFM_FDX;
	else
		ifmr->ifm_active |= IFM_HDX;

	switch (sc->prv.phy.speed) {
	case SPEED_10000:
		ifmr->ifm_active |= IFM_10G_KR;
		break;
	case SPEED_2500:
		ifmr->ifm_active |= IFM_2500_KX;
		break;
	case SPEED_1000:
		ifmr->ifm_active |= IFM_1000_KX;
		break;
	}
}