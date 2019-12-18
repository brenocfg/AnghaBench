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
struct mge_softc {TYPE_1__* ifp; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  MGE_GLOBAL_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_GLOBAL_UNLOCK (struct mge_softc*) ; 
 struct mge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_poll_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  mge_stop (struct mge_softc*) ; 

__attribute__((used)) static int
mge_shutdown(device_t dev)
{
	struct mge_softc *sc = device_get_softc(dev);

	MGE_GLOBAL_LOCK(sc);

#ifdef DEVICE_POLLING
        if (sc->ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(sc->ifp);
#endif

	mge_stop(sc);

	MGE_GLOBAL_UNLOCK(sc);

	return (0);
}