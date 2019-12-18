#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_drv_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver_mtx; struct ifnet* ifp; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxge_open (TYPE_1__*) ; 

__attribute__((used)) static void
mxge_init(void *arg)
{
	mxge_softc_t *sc = arg;
	struct ifnet *ifp = sc->ifp;


	mtx_lock(&sc->driver_mtx);
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		(void) mxge_open(sc);
	mtx_unlock(&sc->driver_mtx);
}