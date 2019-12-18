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
struct ath_softc {int /*<<< orphan*/  sc_txsdma; } ;

/* Variables and functions */
 int HAL_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  ath_descdma_cleanup (struct ath_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_edma_free_txfifo (struct ath_softc*,int) ; 

__attribute__((used)) static int
ath_edma_dma_txteardown(struct ath_softc *sc)
{
	int i;

	for (i = 0; i < HAL_NUM_TX_QUEUES; i++) {
		ath_edma_free_txfifo(sc, i);
	}

	ath_descdma_cleanup(sc, &sc->sc_txsdma, NULL);
	return (0);
}