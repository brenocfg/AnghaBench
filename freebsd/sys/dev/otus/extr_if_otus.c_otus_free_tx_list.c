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
struct otus_softc {int /*<<< orphan*/  sc_tx; int /*<<< orphan*/ * sc_tx_pending; int /*<<< orphan*/ * sc_tx_active; int /*<<< orphan*/  sc_tx_inactive; } ;

/* Variables and functions */
 int OTUS_N_XFER ; 
 int /*<<< orphan*/  OTUS_TX_LIST_COUNT ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otus_free_list (struct otus_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
otus_free_tx_list(struct otus_softc *sc)
{
	int i;

	/* prevent further allocations from TX list(s) */
	STAILQ_INIT(&sc->sc_tx_inactive);

	for (i = 0; i != OTUS_N_XFER; i++) {
		STAILQ_INIT(&sc->sc_tx_active[i]);
		STAILQ_INIT(&sc->sc_tx_pending[i]);
	}

	otus_free_list(sc, sc->sc_tx, OTUS_TX_LIST_COUNT);
}