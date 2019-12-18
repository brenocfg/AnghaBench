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
struct TYPE_2__ {scalar_t__ dd_desc_len; } ;
struct ath_softc {int /*<<< orphan*/  sc_rxbuf; TYPE_1__ sc_rxdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_RX_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_RX_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_RX_QUEUE_HP ; 
 int /*<<< orphan*/  HAL_RX_QUEUE_LP ; 
 int /*<<< orphan*/  ath_descdma_cleanup (struct ath_softc*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_edma_flush_deferred_queue (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_edma_rxfifo_flush (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_edma_rxfifo_free (struct ath_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath_edma_dma_rxteardown(struct ath_softc *sc)
{

	ATH_RX_LOCK(sc);
	ath_edma_flush_deferred_queue(sc);
	ath_edma_rxfifo_flush(sc, HAL_RX_QUEUE_HP);
	ath_edma_rxfifo_free(sc, HAL_RX_QUEUE_HP);

	ath_edma_rxfifo_flush(sc, HAL_RX_QUEUE_LP);
	ath_edma_rxfifo_free(sc, HAL_RX_QUEUE_LP);
	ATH_RX_UNLOCK(sc);

	/* Free RX ath_buf */
	/* Free RX DMA tag */
	if (sc->sc_rxdma.dd_desc_len != 0)
		ath_descdma_cleanup(sc, &sc->sc_rxdma, &sc->sc_rxbuf);

	return (0);
}