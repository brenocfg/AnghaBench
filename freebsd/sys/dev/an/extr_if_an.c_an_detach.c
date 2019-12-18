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
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct an_softc {int an_gone; int /*<<< orphan*/  an_mtx; int /*<<< orphan*/  an_stat_ch; int /*<<< orphan*/  irq_handle; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  an_ifmedia; struct ifnet* an_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AN_LOCK (struct an_softc*) ; 
 int /*<<< orphan*/  AN_UNLOCK (struct an_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  an_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_stop (struct an_softc*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

int
an_detach(device_t dev)
{
	struct an_softc		*sc = device_get_softc(dev);
	struct ifnet		*ifp = sc->an_ifp;

	if (sc->an_gone) {
		device_printf(dev,"already unloaded\n");
		return(0);
	}
	AN_LOCK(sc);
	an_stop(sc);
	sc->an_gone = 1;
	ifmedia_removeall(&sc->an_ifmedia);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	AN_UNLOCK(sc);
	ether_ifdetach(ifp);
	bus_teardown_intr(dev, sc->irq_res, sc->irq_handle);
	callout_drain(&sc->an_stat_ch);
	if_free(ifp);
	an_release_resources(dev);
	mtx_destroy(&sc->an_mtx);
	return (0);
}