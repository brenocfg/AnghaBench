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
struct ifnet {int if_drv_flags; } ;
struct TYPE_2__ {struct ifnet* netdev; } ;
struct axgbe_softc {TYPE_1__ prv; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 

__attribute__((used)) static void
axgbe_init(void *p)
{
	struct axgbe_softc *sc;
	struct ifnet *ifp;

	sc = p;
	ifp = sc->prv.netdev;
	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
}