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
typedef  int uint32_t ;
struct rt_softc {int intr_pending_mask; int int_tx_done_mask; scalar_t__ rt_chipid; int intr_disable_mask; int /*<<< orphan*/  tx_done_task; int /*<<< orphan*/  taskqueue; scalar_t__ tx_timer; int /*<<< orphan*/ * tx_ring; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int INT_TXQ0_DONE ; 
 int INT_TXQ1_DONE ; 
 int INT_TXQ2_DONE ; 
 int INT_TXQ3_DONE ; 
 int RT5350_INT_TXQ0_DONE ; 
 int RT5350_INT_TXQ1_DONE ; 
 int RT5350_INT_TXQ2_DONE ; 
 int RT5350_INT_TXQ3_DONE ; 
 scalar_t__ RT_CHIPID_MT7620 ; 
 scalar_t__ RT_CHIPID_MT7621 ; 
 scalar_t__ RT_CHIPID_RT5350 ; 
 int /*<<< orphan*/  RT_DEBUG_TX ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int RT_SOFTC_TX_RING_COUNT ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_intr_enable (struct rt_softc*,int) ; 
 int /*<<< orphan*/  rt_start (struct ifnet*) ; 
 int /*<<< orphan*/  rt_tx_eof (struct rt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt_tx_done_task(void *context, int pending)
{
	struct rt_softc *sc;
	struct ifnet *ifp;
	uint32_t intr_mask;
	int i;

	sc = context;
	ifp = sc->ifp;

	RT_DPRINTF(sc, RT_DEBUG_TX, "Tx done task\n");

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
		return;

	for (i = RT_SOFTC_TX_RING_COUNT - 1; i >= 0; i--) {
		if (sc->intr_pending_mask & (sc->int_tx_done_mask << i)) {
			sc->intr_pending_mask &= ~(sc->int_tx_done_mask << i);
			rt_tx_eof(sc, &sc->tx_ring[i]);
		}
	}

	sc->tx_timer = 0;

	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	if(sc->rt_chipid == RT_CHIPID_RT5350 ||
	   sc->rt_chipid == RT_CHIPID_MT7620 ||
	   sc->rt_chipid == RT_CHIPID_MT7621)
	  intr_mask = (
		RT5350_INT_TXQ3_DONE |
		RT5350_INT_TXQ2_DONE |
		RT5350_INT_TXQ1_DONE |
		RT5350_INT_TXQ0_DONE);
	else
	  intr_mask = (
		INT_TXQ3_DONE |
		INT_TXQ2_DONE |
		INT_TXQ1_DONE |
		INT_TXQ0_DONE);

	RT_SOFTC_LOCK(sc);

	rt_intr_enable(sc, ~sc->intr_pending_mask &
	    (sc->intr_disable_mask & intr_mask));

	if (sc->intr_pending_mask & intr_mask) {
		RT_DPRINTF(sc, RT_DEBUG_TX,
		    "Tx done task: scheduling again\n");
		taskqueue_enqueue(sc->taskqueue, &sc->tx_done_task);
	}

	RT_SOFTC_UNLOCK(sc);

	if (!IFQ_IS_EMPTY(&ifp->if_snd))
		rt_start(ifp);
}