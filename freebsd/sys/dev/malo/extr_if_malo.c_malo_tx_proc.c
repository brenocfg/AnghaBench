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
struct malo_softc {scalar_t__ malo_timer; TYPE_1__* malo_txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALO_LOCK (struct malo_softc*) ; 
 int MALO_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  MALO_UNLOCK (struct malo_softc*) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malo_start (struct malo_softc*) ; 
 scalar_t__ malo_tx_processq (struct malo_softc*,TYPE_1__*) ; 

__attribute__((used)) static void
malo_tx_proc(void *arg, int npending)
{
	struct malo_softc *sc = arg;
	int i, nreaped;

	/*
	 * Process each active queue.
	 */
	nreaped = 0;
	MALO_LOCK(sc);
	for (i = 0; i < MALO_NUM_TX_QUEUES; i++) {
		if (!STAILQ_EMPTY(&sc->malo_txq[i].active))
			nreaped += malo_tx_processq(sc, &sc->malo_txq[i]);
	}

	if (nreaped != 0) {
		sc->malo_timer = 0;
		malo_start(sc);
	}
	MALO_UNLOCK(sc);
}