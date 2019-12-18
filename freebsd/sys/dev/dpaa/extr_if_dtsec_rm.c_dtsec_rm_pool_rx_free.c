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
struct dtsec_softc {int /*<<< orphan*/ * sc_rx_zone; int /*<<< orphan*/ * sc_rx_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  bman_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ *) ; 

void
dtsec_rm_pool_rx_free(struct dtsec_softc *sc)
{

	if (sc->sc_rx_pool != NULL)
		bman_pool_destroy(sc->sc_rx_pool);

	if (sc->sc_rx_zone != NULL)
		uma_zdestroy(sc->sc_rx_zone);
}