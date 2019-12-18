#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octm_softc {int /*<<< orphan*/  sc_port; } ;
struct ifnet {struct octm_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct TYPE_4__ {int speed; scalar_t__ full_duplex; int /*<<< orphan*/  link_up; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_100_TX ; 
 int /*<<< orphan*/  IFM_10G_T ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 TYPE_2__ cvmx_mgmt_port_link_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
octm_medstat(struct ifnet *ifp, struct ifmediareq *ifm)
{
	struct octm_softc *sc;
	cvmx_helper_link_info_t link_info;

	sc = ifp->if_softc;

	ifm->ifm_status = IFM_AVALID;
	ifm->ifm_active = IFT_ETHER;

	link_info = cvmx_mgmt_port_link_get(sc->sc_port);
	if (!link_info.s.link_up)
		return;

	ifm->ifm_status |= IFM_ACTIVE;

	switch (link_info.s.speed) {
	case 10:
		ifm->ifm_active |= IFM_10_T;
		break;
	case 100:
		ifm->ifm_active |= IFM_100_TX;
		break;
	case 1000:
		ifm->ifm_active |= IFM_1000_T;
		break;
	case 10000:
		ifm->ifm_active |= IFM_10G_T;
		break;
	}

	if (link_info.s.full_duplex)
		ifm->ifm_active |= IFM_FDX;
	else
		ifm->ifm_active |= IFM_HDX;
}