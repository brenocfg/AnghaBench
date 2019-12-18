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
struct TYPE_2__ {int /*<<< orphan*/  recv_sched_queue; int /*<<< orphan*/  recv_sched; int /*<<< orphan*/  recv_teardown; int /*<<< orphan*/  recv_setup; int /*<<< orphan*/  recv_rxbuf_init; int /*<<< orphan*/  recv_tasklet; int /*<<< orphan*/  recv_flush; int /*<<< orphan*/  recv_start; int /*<<< orphan*/  recv_stop; } ;
struct ath_softc {int sc_edma_bufsize; int sc_rx_statuslen; TYPE_1__ sc_rx; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_edma_dma_rxsetup ; 
 int /*<<< orphan*/  ath_edma_dma_rxteardown ; 
 int /*<<< orphan*/  ath_edma_recv_flush ; 
 int /*<<< orphan*/  ath_edma_recv_sched ; 
 int /*<<< orphan*/  ath_edma_recv_sched_queue ; 
 int /*<<< orphan*/  ath_edma_recv_tasklet ; 
 int /*<<< orphan*/  ath_edma_rxbuf_init ; 
 int /*<<< orphan*/  ath_edma_startrecv ; 
 int /*<<< orphan*/  ath_edma_stoprecv ; 
 int /*<<< orphan*/  ath_hal_getrxstatuslen (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ath_hal_setrxbufsize (int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

void
ath_recv_setup_edma(struct ath_softc *sc)
{

	/* Set buffer size to 4k */
	sc->sc_edma_bufsize = 4096;

	/* Fetch EDMA field and buffer sizes */
	(void) ath_hal_getrxstatuslen(sc->sc_ah, &sc->sc_rx_statuslen);

	/* Configure the hardware with the RX buffer size */
	(void) ath_hal_setrxbufsize(sc->sc_ah, sc->sc_edma_bufsize -
	    sc->sc_rx_statuslen);

	if (bootverbose) {
		device_printf(sc->sc_dev, "RX status length: %d\n",
		    sc->sc_rx_statuslen);
		device_printf(sc->sc_dev, "RX buffer size: %d\n",
		    sc->sc_edma_bufsize);
	}

	sc->sc_rx.recv_stop = ath_edma_stoprecv;
	sc->sc_rx.recv_start = ath_edma_startrecv;
	sc->sc_rx.recv_flush = ath_edma_recv_flush;
	sc->sc_rx.recv_tasklet = ath_edma_recv_tasklet;
	sc->sc_rx.recv_rxbuf_init = ath_edma_rxbuf_init;

	sc->sc_rx.recv_setup = ath_edma_dma_rxsetup;
	sc->sc_rx.recv_teardown = ath_edma_dma_rxteardown;

	sc->sc_rx.recv_sched = ath_edma_recv_sched;
	sc->sc_rx.recv_sched_queue = ath_edma_recv_sched_queue;
}