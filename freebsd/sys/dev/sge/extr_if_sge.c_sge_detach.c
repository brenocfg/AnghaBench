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
struct sge_softc {int /*<<< orphan*/  sge_mtx; scalar_t__ sge_res; int /*<<< orphan*/  sge_res_id; int /*<<< orphan*/  sge_res_type; scalar_t__ sge_irq; scalar_t__ sge_intrhand; scalar_t__ sge_miibus; int /*<<< orphan*/  sge_stat_ch; struct ifnet* sge_ifp; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SGE_LOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  SGE_UNLOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct sge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sge_dma_free (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_stop (struct sge_softc*) ; 

__attribute__((used)) static int
sge_detach(device_t dev)
{
	struct sge_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	ifp = sc->sge_ifp;
	/* These should only be active if attach succeeded. */
	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		SGE_LOCK(sc);
		sge_stop(sc);
		SGE_UNLOCK(sc);
		callout_drain(&sc->sge_stat_ch);
	}
	if (sc->sge_miibus)
		device_delete_child(dev, sc->sge_miibus);
	bus_generic_detach(dev);

	if (sc->sge_intrhand)
		bus_teardown_intr(dev, sc->sge_irq, sc->sge_intrhand);
	if (sc->sge_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sge_irq);
	if (sc->sge_res)
		bus_release_resource(dev, sc->sge_res_type, sc->sge_res_id,
		    sc->sge_res);
	if (ifp)
		if_free(ifp);
	sge_dma_free(sc);
	mtx_destroy(&sc->sge_mtx);

	return (0);
}