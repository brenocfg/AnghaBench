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
struct rt_softc {int rx_ring_count; int /*<<< orphan*/  mem; int /*<<< orphan*/  mem_rid; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/  irqh; int /*<<< orphan*/  lock; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/ * rt_miibus; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  periodic_task; int /*<<< orphan*/  tx_done_task; int /*<<< orphan*/  rx_done_task; int /*<<< orphan*/  tx_watchdog_ch; int /*<<< orphan*/  periodic_ch; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  RT_DEBUG_ANY ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int RT_SOFTC_TX_RING_COUNT ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_free_rx_ring (struct rt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_free_tx_ring (struct rt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rt_detach(device_t dev)
{
	struct rt_softc *sc;
	struct ifnet *ifp;
	int i;

	sc = device_get_softc(dev);
	ifp = sc->ifp;

	RT_DPRINTF(sc, RT_DEBUG_ANY, "detaching\n");

	RT_SOFTC_LOCK(sc);

	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);

	callout_stop(&sc->periodic_ch);
	callout_stop(&sc->tx_watchdog_ch);

	taskqueue_drain(sc->taskqueue, &sc->rx_done_task);
	taskqueue_drain(sc->taskqueue, &sc->tx_done_task);
	taskqueue_drain(sc->taskqueue, &sc->periodic_task);

	/* free Tx and Rx rings */
	for (i = 0; i < RT_SOFTC_TX_RING_COUNT; i++)
		rt_free_tx_ring(sc, &sc->tx_ring[i]);
	for (i = 0; i < sc->rx_ring_count; i++)
		rt_free_rx_ring(sc, &sc->rx_ring[i]);

	RT_SOFTC_UNLOCK(sc);

#ifdef IF_RT_PHY_SUPPORT
	if (sc->rt_miibus != NULL)
		device_delete_child(dev, sc->rt_miibus);
#endif

	ether_ifdetach(ifp);
	if_free(ifp);

	taskqueue_free(sc->taskqueue);

	mtx_destroy(&sc->lock);

	bus_generic_detach(dev);
	bus_teardown_intr(dev, sc->irq, sc->irqh);
	bus_release_resource(dev, SYS_RES_IRQ, sc->irq_rid, sc->irq);
	bus_release_resource(dev, SYS_RES_MEMORY, sc->mem_rid, sc->mem);

	return (0);
}