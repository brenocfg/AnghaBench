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
struct rt_softc {int intr_pending_mask; int int_rx_done_mask; int /*<<< orphan*/  rx_done_task; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/  rx_process_limit; int /*<<< orphan*/ * rx_ring; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  RT_DEBUG_RX ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_intr_enable (struct rt_softc*,int) ; 
 int rt_rx_eof (struct rt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt_rx_done_task(void *context, int pending)
{
	struct rt_softc *sc;
	struct ifnet *ifp;
	int again;

	sc = context;
	ifp = sc->ifp;

	RT_DPRINTF(sc, RT_DEBUG_RX, "Rx done task\n");

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
		return;

	sc->intr_pending_mask &= ~sc->int_rx_done_mask;

	again = rt_rx_eof(sc, &sc->rx_ring[0], sc->rx_process_limit);

	RT_SOFTC_LOCK(sc);

	if ((sc->intr_pending_mask & sc->int_rx_done_mask) || again) {
		RT_DPRINTF(sc, RT_DEBUG_RX,
		    "Rx done task: scheduling again\n");
		taskqueue_enqueue(sc->taskqueue, &sc->rx_done_task);
	} else {
		rt_intr_enable(sc, sc->int_rx_done_mask);
	}

	RT_SOFTC_UNLOCK(sc);
}