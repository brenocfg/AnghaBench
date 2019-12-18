#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ifnet {struct axgbe_softc* if_softc; } ;
struct TYPE_9__ {int (* phy_config_aneg ) (TYPE_5__*) ;} ;
struct TYPE_8__ {void* autoneg; int /*<<< orphan*/  speed; } ;
struct TYPE_10__ {TYPE_4__ phy_if; int /*<<< orphan*/  an_mutex; TYPE_3__ phy; } ;
struct TYPE_7__ {TYPE_1__* ifm_cur; } ;
struct axgbe_softc {TYPE_5__ prv; TYPE_2__ media; } ;
struct TYPE_6__ {int ifm_media; } ;

/* Variables and functions */
 void* AUTONEG_DISABLE ; 
 void* AUTONEG_ENABLE ; 
#define  IFM_1000_KX 131 
#define  IFM_10G_KR 130 
#define  IFM_2500_KX 129 
#define  IFM_AUTO 128 
 int IFM_SUBTYPE (int) ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
axgbe_media_change(struct ifnet *ifp)
{
	struct axgbe_softc *sc;
	int cur_media;

	sc = ifp->if_softc;

	sx_xlock(&sc->prv.an_mutex);
	cur_media = sc->media.ifm_cur->ifm_media;

	switch (IFM_SUBTYPE(cur_media)) {
	case IFM_10G_KR:
		sc->prv.phy.speed = SPEED_10000;
		sc->prv.phy.autoneg = AUTONEG_DISABLE;
		break;
	case IFM_2500_KX:
		sc->prv.phy.speed = SPEED_2500;
		sc->prv.phy.autoneg = AUTONEG_DISABLE;
		break;
	case IFM_1000_KX:
		sc->prv.phy.speed = SPEED_1000;
		sc->prv.phy.autoneg = AUTONEG_DISABLE;
		break;
	case IFM_AUTO:
		sc->prv.phy.autoneg = AUTONEG_ENABLE;
		break;
	}
	sx_xunlock(&sc->prv.an_mutex);

	return (-sc->prv.phy_if.phy_config_aneg(&sc->prv));
}