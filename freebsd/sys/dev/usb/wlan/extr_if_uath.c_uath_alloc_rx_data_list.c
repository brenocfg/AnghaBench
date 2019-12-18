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
struct uath_softc {int /*<<< orphan*/ * sc_rx; int /*<<< orphan*/  sc_rx_inactive; int /*<<< orphan*/  sc_rx_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int UATH_RX_DATA_LIST_COUNT ; 
 int /*<<< orphan*/  UATH_STAT_INC (struct uath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  st_rx_inactive ; 
 int uath_alloc_data_list (struct uath_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uath_alloc_rx_data_list(struct uath_softc *sc)
{
	int error, i;

	/* XXX is it enough to store the RX packet with MCLBYTES bytes?  */
	error = uath_alloc_data_list(sc,
	    sc->sc_rx, UATH_RX_DATA_LIST_COUNT, MCLBYTES,
	    NULL /* setup mbufs */);
	if (error != 0)
		return (error);

	STAILQ_INIT(&sc->sc_rx_active);
	STAILQ_INIT(&sc->sc_rx_inactive);

	for (i = 0; i < UATH_RX_DATA_LIST_COUNT; i++) {
		STAILQ_INSERT_HEAD(&sc->sc_rx_inactive, &sc->sc_rx[i],
		    next);
		UATH_STAT_INC(sc, st_rx_inactive);
	}

	return (0);
}