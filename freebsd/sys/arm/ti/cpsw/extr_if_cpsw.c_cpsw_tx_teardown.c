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
struct TYPE_2__ {int teardown; int /*<<< orphan*/  active_queue_len; scalar_t__ running; int /*<<< orphan*/  active; } ;
struct cpsw_softc {TYPE_1__ tx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_TX_TEARDOWN ; 
 int /*<<< orphan*/  CPSW_DEBUGF (struct cpsw_softc*,char*) ; 
 int /*<<< orphan*/  CPSW_TX_LOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  CPSW_TX_UNLOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_tx_dequeue (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cpsw_tx_teardown(struct cpsw_softc *sc)
{
	int i = 0;

	CPSW_TX_LOCK(sc);
	CPSW_DEBUGF(sc, ("starting TX teardown"));
	/* Start the TX queue teardown if queue is not empty. */
	if (STAILQ_FIRST(&sc->tx.active) != NULL)
		cpsw_write_4(sc, CPSW_CPDMA_TX_TEARDOWN, 0);
	else
		sc->tx.teardown = 1;
	cpsw_tx_dequeue(sc);
	while (sc->tx.running && ++i < 10) {
		DELAY(200);
		cpsw_tx_dequeue(sc);
	}
	if (sc->tx.running) {
		device_printf(sc->dev,
		    "Unable to cleanly shutdown transmitter\n");
	}
	CPSW_DEBUGF(sc,
	    ("finished TX teardown (%d retries, %d idle buffers)", i,
	     sc->tx.active_queue_len));
	CPSW_TX_UNLOCK(sc);
}