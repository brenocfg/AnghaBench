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
struct otus_softc {scalar_t__ sc_running; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  calib_to; int /*<<< orphan*/  scan_to; scalar_t__ sc_tx_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MAC_REG_DMA_TRIGGER ; 
 int /*<<< orphan*/  OTUS_LOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  OTUS_UNLOCK (struct otus_softc*) ; 
 int /*<<< orphan*/  OTUS_UNLOCK_ASSERT (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_drain_mbufq (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otus_write_barrier (struct otus_softc*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

void
otus_stop(struct otus_softc *sc)
{
#if 0
	int s;
#endif

	OTUS_UNLOCK_ASSERT(sc);

	OTUS_LOCK(sc);
	sc->sc_running = 0;
	sc->sc_tx_timer = 0;
	OTUS_UNLOCK(sc);

	taskqueue_drain_timeout(taskqueue_thread, &sc->scan_to);
	taskqueue_drain_timeout(taskqueue_thread, &sc->calib_to);
	taskqueue_drain(taskqueue_thread, &sc->tx_task);

	OTUS_LOCK(sc);
	sc->sc_running = 0;
	/* Stop Rx. */
	otus_write(sc, AR_MAC_REG_DMA_TRIGGER, 0);
	(void)otus_write_barrier(sc);

	/* Drain any pending TX frames */
	otus_drain_mbufq(sc);

	OTUS_UNLOCK(sc);
}