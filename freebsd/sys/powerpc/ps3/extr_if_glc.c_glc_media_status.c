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
typedef  int uint64_t ;
struct ifnet {struct glc_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct glc_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 int GELIC_FULL_DUPLEX ; 
 int /*<<< orphan*/  GELIC_GET_LINK_STATUS ; 
 int GELIC_LINK_UP ; 
 int GELIC_SPEED_10 ; 
 int GELIC_SPEED_100 ; 
 int GELIC_SPEED_1000 ; 
 int /*<<< orphan*/  GELIC_VLAN_TX_ETHERNET ; 
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_100_TX ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_HDX ; 
 int /*<<< orphan*/  lv1_net_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
glc_media_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct glc_softc *sc = ifp->if_softc; 
	uint64_t status, junk;

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	lv1_net_control(sc->sc_bus, sc->sc_dev, GELIC_GET_LINK_STATUS,
	    GELIC_VLAN_TX_ETHERNET, 0, 0, &status, &junk);

	if (status & GELIC_LINK_UP)
		ifmr->ifm_status |= IFM_ACTIVE;

	if (status & GELIC_SPEED_10)
		ifmr->ifm_active |= IFM_10_T;
	else if (status & GELIC_SPEED_100)
		ifmr->ifm_active |= IFM_100_TX;
	else if (status & GELIC_SPEED_1000)
		ifmr->ifm_active |= IFM_1000_T;

	if (status & GELIC_FULL_DUPLEX)
		ifmr->ifm_active |= IFM_FDX;
	else
		ifmr->ifm_active |= IFM_HDX;
}