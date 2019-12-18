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
struct mwl_softc {int /*<<< orphan*/ * sc_txq; } ;

/* Variables and functions */
 int MWL_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  mwl_dma_cleanup (struct mwl_softc*) ; 
 int /*<<< orphan*/  mwl_rxdma_cleanup (struct mwl_softc*) ; 
 int mwl_rxdma_setup (struct mwl_softc*) ; 
 int mwl_txdma_setup (struct mwl_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwl_dma_setup(struct mwl_softc *sc)
{
	int error, i;

	error = mwl_rxdma_setup(sc);
	if (error != 0) {
		mwl_rxdma_cleanup(sc);
		return error;
	}

	for (i = 0; i < MWL_NUM_TX_QUEUES; i++) {
		error = mwl_txdma_setup(sc, &sc->sc_txq[i]);
		if (error != 0) {
			mwl_dma_cleanup(sc);
			return error;
		}
	}
	return 0;
}