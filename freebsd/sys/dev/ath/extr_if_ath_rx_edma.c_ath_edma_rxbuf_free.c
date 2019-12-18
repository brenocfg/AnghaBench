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
struct ath_softc {int /*<<< orphan*/  sc_rxbuf; int /*<<< orphan*/  sc_dmat; } ;
struct ath_buf {int /*<<< orphan*/ * bf_m; int /*<<< orphan*/  bf_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_RX_LOCK_ASSERT (struct ath_softc*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ath_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_list ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_edma_rxbuf_free(struct ath_softc *sc, struct ath_buf *bf)
{

	ATH_RX_LOCK_ASSERT(sc);

	/*
	 * Only unload the frame if we haven't consumed
	 * the mbuf via ath_rx_pkt().
	 */
	if (bf->bf_m) {
		bus_dmamap_unload(sc->sc_dmat, bf->bf_dmamap);
		m_freem(bf->bf_m);
		bf->bf_m = NULL;
	}

	/* XXX lock? */
	TAILQ_INSERT_TAIL(&sc->sc_rxbuf, bf, bf_list);
}