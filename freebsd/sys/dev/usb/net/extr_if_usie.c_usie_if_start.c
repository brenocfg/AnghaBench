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
struct usie_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_if_xfer; } ;
struct ifnet {int if_drv_flags; struct usie_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int IFF_DRV_RUNNING ; 
 size_t USIE_IF_TX ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usie_if_start(struct ifnet *ifp)
{
	struct usie_softc *sc = ifp->if_softc;

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING)) {
		DPRINTF("Not running\n");
		return;
	}
	mtx_lock(&sc->sc_mtx);
	usbd_transfer_start(sc->sc_if_xfer[USIE_IF_TX]);
	mtx_unlock(&sc->sc_mtx);

	DPRINTFN(3, "interface started\n");
}