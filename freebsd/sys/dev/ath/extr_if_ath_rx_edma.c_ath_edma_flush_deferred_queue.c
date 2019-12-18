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
struct ath_softc {int /*<<< orphan*/ * sc_rx_rxlist; } ;
struct ath_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_RX_LOCK_ASSERT (struct ath_softc*) ; 
 size_t HAL_RX_QUEUE_HP ; 
 size_t HAL_RX_QUEUE_LP ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ath_buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ath_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_edma_rxbuf_free (struct ath_softc*,struct ath_buf*) ; 
 int /*<<< orphan*/  bf_list ; 

__attribute__((used)) static void
ath_edma_flush_deferred_queue(struct ath_softc *sc)
{
	struct ath_buf *bf;

	ATH_RX_LOCK_ASSERT(sc);

	/* Free in one set, inside the lock */
	while (! TAILQ_EMPTY(&sc->sc_rx_rxlist[HAL_RX_QUEUE_LP])) {
		bf = TAILQ_FIRST(&sc->sc_rx_rxlist[HAL_RX_QUEUE_LP]);
		TAILQ_REMOVE(&sc->sc_rx_rxlist[HAL_RX_QUEUE_LP], bf, bf_list);
		/* Free the buffer/mbuf */
		ath_edma_rxbuf_free(sc, bf);
	}
	while (! TAILQ_EMPTY(&sc->sc_rx_rxlist[HAL_RX_QUEUE_HP])) {
		bf = TAILQ_FIRST(&sc->sc_rx_rxlist[HAL_RX_QUEUE_HP]);
		TAILQ_REMOVE(&sc->sc_rx_rxlist[HAL_RX_QUEUE_HP], bf, bf_list);
		/* Free the buffer/mbuf */
		ath_edma_rxbuf_free(sc, bf);
	}
}