#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  recv_sched_queue; int /*<<< orphan*/  recv_sched; int /*<<< orphan*/  recv_teardown; int /*<<< orphan*/  recv_setup; int /*<<< orphan*/  recv_rxbuf_init; int /*<<< orphan*/  recv_tasklet; int /*<<< orphan*/  recv_flush; int /*<<< orphan*/  recv_stop; int /*<<< orphan*/  recv_start; } ;
struct ath_softc {int sc_rx_statuslen; TYPE_1__ sc_rx; } ;
struct ath_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_legacy_dma_rxsetup ; 
 int /*<<< orphan*/  ath_legacy_dma_rxteardown ; 
 int /*<<< orphan*/  ath_legacy_flushrecv ; 
 int /*<<< orphan*/  ath_legacy_recv_sched ; 
 int /*<<< orphan*/  ath_legacy_recv_sched_queue ; 
 int /*<<< orphan*/  ath_legacy_rx_tasklet ; 
 int /*<<< orphan*/  ath_legacy_rxbuf_init ; 
 int /*<<< orphan*/  ath_legacy_startrecv ; 
 int /*<<< orphan*/  ath_legacy_stoprecv ; 

void
ath_recv_setup_legacy(struct ath_softc *sc)
{

	/* Sensible legacy defaults */
	/*
	 * XXX this should be changed to properly support the
	 * exact RX descriptor size for each HAL.
	 */
	sc->sc_rx_statuslen = sizeof(struct ath_desc);

	sc->sc_rx.recv_start = ath_legacy_startrecv;
	sc->sc_rx.recv_stop = ath_legacy_stoprecv;
	sc->sc_rx.recv_flush = ath_legacy_flushrecv;
	sc->sc_rx.recv_tasklet = ath_legacy_rx_tasklet;
	sc->sc_rx.recv_rxbuf_init = ath_legacy_rxbuf_init;

	sc->sc_rx.recv_setup = ath_legacy_dma_rxsetup;
	sc->sc_rx.recv_teardown = ath_legacy_dma_rxteardown;
	sc->sc_rx.recv_sched = ath_legacy_recv_sched;
	sc->sc_rx.recv_sched_queue = ath_legacy_recv_sched_queue;
}