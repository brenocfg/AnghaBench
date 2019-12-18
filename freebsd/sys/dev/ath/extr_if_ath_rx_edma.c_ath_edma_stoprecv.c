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
struct ath_softc {int sc_rx_stopped; TYPE_1__* sc_rxedma; struct ath_hal* sc_ah; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * m_rxpending; } ;

/* Variables and functions */
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  ATH_RX_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_RX_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 size_t HAL_RX_QUEUE_HP ; 
 size_t HAL_RX_QUEUE_LP ; 
 int /*<<< orphan*/  ath_hal_setrxfilter (struct ath_hal*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath_hal_stopdmarecv (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_stoppcurecv (struct ath_hal*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_edma_stoprecv(struct ath_softc *sc, int dodelay)
{
	struct ath_hal *ah = sc->sc_ah;

	ATH_RX_LOCK(sc);

	ath_hal_stoppcurecv(ah);
	ath_hal_setrxfilter(ah, 0);

	/*
	 *
	 */
	if (ath_hal_stopdmarecv(ah) == AH_TRUE)
		sc->sc_rx_stopped = 1;

	/*
	 * Give the various bus FIFOs (not EDMA descriptor FIFO)
	 * time to finish flushing out data.
	 */
	DELAY(3000);

	/* Flush RX pending for each queue */
	/* XXX should generic-ify this */
	if (sc->sc_rxedma[HAL_RX_QUEUE_HP].m_rxpending) {
		m_freem(sc->sc_rxedma[HAL_RX_QUEUE_HP].m_rxpending);
		sc->sc_rxedma[HAL_RX_QUEUE_HP].m_rxpending = NULL;
	}

	if (sc->sc_rxedma[HAL_RX_QUEUE_LP].m_rxpending) {
		m_freem(sc->sc_rxedma[HAL_RX_QUEUE_LP].m_rxpending);
		sc->sc_rxedma[HAL_RX_QUEUE_LP].m_rxpending = NULL;
	}
	ATH_RX_UNLOCK(sc);
}