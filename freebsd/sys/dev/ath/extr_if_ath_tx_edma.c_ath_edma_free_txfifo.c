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
struct ath_tx_edma_fifo {int /*<<< orphan*/  m_fifo; } ;
struct ath_softc {struct ath_tx_edma_fifo* sc_txedma; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ATHDEV ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath_edma_free_txfifo(struct ath_softc *sc, int qnum)
{
	struct ath_tx_edma_fifo *te = &sc->sc_txedma[qnum];

	/* XXX TODO: actually deref the ath_buf entries? */
	free(te->m_fifo, M_ATHDEV);
	return (0);
}