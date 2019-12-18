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
struct otus_softc {int /*<<< orphan*/ * sc_tx; int /*<<< orphan*/  sc_tx_inactive; int /*<<< orphan*/ * sc_tx_pending; int /*<<< orphan*/ * sc_tx_active; } ;

/* Variables and functions */
 int OTUS_N_XFER ; 
 int /*<<< orphan*/  OTUS_TXBUFSZ ; 
 int OTUS_TX_LIST_COUNT ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int otus_alloc_list (struct otus_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
otus_alloc_tx_list(struct otus_softc *sc)
{
	int error, i;

	error = otus_alloc_list(sc, sc->sc_tx, OTUS_TX_LIST_COUNT,
	    OTUS_TXBUFSZ);
	if (error != 0)
		return (error);

	STAILQ_INIT(&sc->sc_tx_inactive);

	for (i = 0; i != OTUS_N_XFER; i++) {
		STAILQ_INIT(&sc->sc_tx_active[i]);
		STAILQ_INIT(&sc->sc_tx_pending[i]);
	}

	for (i = 0; i < OTUS_TX_LIST_COUNT; i++) {
		STAILQ_INSERT_HEAD(&sc->sc_tx_inactive, &sc->sc_tx[i], next);
	}

	return (0);
}