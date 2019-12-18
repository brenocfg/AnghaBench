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
 int /*<<< orphan*/  mwl_tx_cleanupq (struct mwl_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwl_tx_cleanup(struct mwl_softc *sc)
{
	int i;

	for (i = 0; i < MWL_NUM_TX_QUEUES; i++)
		mwl_tx_cleanupq(sc, &sc->sc_txq[i]);
}