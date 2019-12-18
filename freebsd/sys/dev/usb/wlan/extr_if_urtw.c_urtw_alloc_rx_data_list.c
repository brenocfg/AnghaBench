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
struct urtw_softc {int /*<<< orphan*/ * sc_rx; int /*<<< orphan*/  sc_rx_inactive; int /*<<< orphan*/  sc_rx_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int URTW_RX_DATA_LIST_COUNT ; 
 int /*<<< orphan*/  next ; 
 int urtw_alloc_data_list (struct urtw_softc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
urtw_alloc_rx_data_list(struct urtw_softc *sc)
{
	int error, i;

	error = urtw_alloc_data_list(sc,
	    sc->sc_rx, URTW_RX_DATA_LIST_COUNT,
	    MCLBYTES, NULL /* mbufs */);
	if (error != 0)
		return (error);

	STAILQ_INIT(&sc->sc_rx_active);
	STAILQ_INIT(&sc->sc_rx_inactive);

	for (i = 0; i < URTW_RX_DATA_LIST_COUNT; i++)
		STAILQ_INSERT_HEAD(&sc->sc_rx_inactive, &sc->sc_rx[i], next);

	return (0);
}