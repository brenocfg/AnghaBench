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
struct malo_softc {int /*<<< orphan*/ * malo_txq; } ;

/* Variables and functions */
 int MALO_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  malo_dma_cleanup (struct malo_softc*) ; 
 int malo_rxdma_setup (struct malo_softc*) ; 
 int malo_txdma_setup (struct malo_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malo_txq_init (struct malo_softc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
malo_dma_setup(struct malo_softc *sc)
{
	int error, i;

	/* rxdma initializing.  */
	error = malo_rxdma_setup(sc);
	if (error != 0)
		return error;

	/* NB: we just have 1 tx queue now.  */
	for (i = 0; i < MALO_NUM_TX_QUEUES; i++) {
		error = malo_txdma_setup(sc, &sc->malo_txq[i]);
		if (error != 0) {
			malo_dma_cleanup(sc);

			return error;
		}

		malo_txq_init(sc, &sc->malo_txq[i], i);
	}

	return 0;
}