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
struct my_softc {int /*<<< orphan*/  my_mtx; int /*<<< orphan*/  my_res; int /*<<< orphan*/  my_irq; int /*<<< orphan*/  my_ldata_ptr; int /*<<< orphan*/  my_autoneg_timer; int /*<<< orphan*/  my_watchdog; int /*<<< orphan*/  my_intrhand; struct ifnet* my_ifp; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MY_LOCK (struct my_softc*) ; 
 int /*<<< orphan*/  MY_RES ; 
 int /*<<< orphan*/  MY_RID ; 
 int /*<<< orphan*/  MY_UNLOCK (struct my_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct my_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  my_stop (struct my_softc*) ; 

__attribute__((used)) static int
my_detach(device_t dev)
{
	struct my_softc *sc;
	struct ifnet   *ifp;

	sc = device_get_softc(dev);
	ifp = sc->my_ifp;
	ether_ifdetach(ifp);
	MY_LOCK(sc);
	my_stop(sc);
	MY_UNLOCK(sc);
	bus_teardown_intr(dev, sc->my_irq, sc->my_intrhand);
	callout_drain(&sc->my_watchdog);
	callout_drain(&sc->my_autoneg_timer);

	if_free(ifp);
	free(sc->my_ldata_ptr, M_DEVBUF);

	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->my_irq);
	bus_release_resource(dev, MY_RES, MY_RID, sc->my_res);
	mtx_destroy(&sc->my_mtx);
	return (0);
}