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
struct ath_softc {int /*<<< orphan*/  sc_rx_statuslen; int /*<<< orphan*/  sc_rxbuf; int /*<<< orphan*/  sc_rxdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_RX_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_RX_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_RX_QUEUE_HP ; 
 int /*<<< orphan*/  HAL_RX_QUEUE_LP ; 
 int ath_descdma_setup_rx_edma (struct ath_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_edma_setup_rxfifo (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_rxbuf ; 

__attribute__((used)) static int
ath_edma_dma_rxsetup(struct ath_softc *sc)
{
	int error;

	/*
	 * Create RX DMA tag and buffers.
	 */
	error = ath_descdma_setup_rx_edma(sc, &sc->sc_rxdma, &sc->sc_rxbuf,
	    "rx", ath_rxbuf, sc->sc_rx_statuslen);
	if (error != 0)
		return error;

	ATH_RX_LOCK(sc);
	(void) ath_edma_setup_rxfifo(sc, HAL_RX_QUEUE_HP);
	(void) ath_edma_setup_rxfifo(sc, HAL_RX_QUEUE_LP);
	ATH_RX_UNLOCK(sc);

	return (0);
}