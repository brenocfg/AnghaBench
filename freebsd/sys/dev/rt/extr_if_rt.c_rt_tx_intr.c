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
struct rt_softc {int intr_disable_mask; int int_tx_done_mask; int intr_pending_mask; int /*<<< orphan*/  tx_done_task; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/ * tx_interrupts; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RT_DEBUG_INTR ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int RT_SOFTC_TX_RING_COUNT ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_intr_disable (struct rt_softc*,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt_tx_intr(struct rt_softc *sc, int qid)
{

	KASSERT(qid >= 0 && qid < RT_SOFTC_TX_RING_COUNT,
		("%s: Tx interrupt: invalid qid=%d\n",
		 device_get_nameunit(sc->dev), qid));

	RT_DPRINTF(sc, RT_DEBUG_INTR, "Tx interrupt: qid=%d\n", qid);

	sc->tx_interrupts[qid]++;
	RT_SOFTC_LOCK(sc);

	if (!(sc->intr_disable_mask & (sc->int_tx_done_mask << qid))) {
		rt_intr_disable(sc, (sc->int_tx_done_mask << qid));
		taskqueue_enqueue(sc->taskqueue, &sc->tx_done_task);
	}

	sc->intr_pending_mask |= (sc->int_tx_done_mask << qid);
	RT_SOFTC_UNLOCK(sc);
}