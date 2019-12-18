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
struct urtw_softc {int /*<<< orphan*/ * sc_tx; int /*<<< orphan*/  sc_tx_inactive; int /*<<< orphan*/  sc_tx_pending; int /*<<< orphan*/  sc_tx_active; int /*<<< orphan*/  sc_tx_dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int URTW_TX_DATA_LIST_COUNT ; 
 int /*<<< orphan*/  URTW_TX_MAXSIZE ; 
 int /*<<< orphan*/  next ; 
 int urtw_alloc_data_list (struct urtw_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
urtw_alloc_tx_data_list(struct urtw_softc *sc)
{
	int error, i;

	error = urtw_alloc_data_list(sc,
	    sc->sc_tx, URTW_TX_DATA_LIST_COUNT, URTW_TX_MAXSIZE,
	    sc->sc_tx_dma_buf /* no mbufs */);
	if (error != 0)
		return (error);

	STAILQ_INIT(&sc->sc_tx_active);
	STAILQ_INIT(&sc->sc_tx_inactive);
	STAILQ_INIT(&sc->sc_tx_pending);

	for (i = 0; i < URTW_TX_DATA_LIST_COUNT; i++)
		STAILQ_INSERT_HEAD(&sc->sc_tx_inactive, &sc->sc_tx[i],
		    next);

	return (0);
}