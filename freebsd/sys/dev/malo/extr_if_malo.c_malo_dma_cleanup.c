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
 int /*<<< orphan*/  malo_rxdma_cleanup (struct malo_softc*) ; 
 int /*<<< orphan*/  malo_txdma_cleanup (struct malo_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
malo_dma_cleanup(struct malo_softc *sc)
{
	int i;

	for (i = 0; i < MALO_NUM_TX_QUEUES; i++)
		malo_txdma_cleanup(sc, &sc->malo_txq[i]);

	malo_rxdma_cleanup(sc);
}