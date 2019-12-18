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
struct uhso_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_if_xfer; } ;
struct ifnet {int if_drv_flags; struct uhso_softc* if_softc; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*) ; 
 size_t UHSO_IFNET_READ ; 
 size_t UHSO_IFNET_WRITE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhso_if_start(struct ifnet *ifp)
{
	struct uhso_softc *sc = ifp->if_softc;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		UHSO_DPRINTF(1, "Not running\n");
		return;
	}

	mtx_lock(&sc->sc_mtx);
	usbd_transfer_start(sc->sc_if_xfer[UHSO_IFNET_READ]);
	usbd_transfer_start(sc->sc_if_xfer[UHSO_IFNET_WRITE]);
	mtx_unlock(&sc->sc_mtx);
	UHSO_DPRINTF(3, "interface started\n");
}