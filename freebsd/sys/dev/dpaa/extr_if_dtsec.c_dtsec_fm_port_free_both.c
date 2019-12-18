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
struct dtsec_softc {int /*<<< orphan*/ * sc_txph; int /*<<< orphan*/ * sc_rxph; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_PORT_Free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtsec_fm_port_free_both(struct dtsec_softc *sc)
{
	if (sc->sc_rxph) {
		FM_PORT_Free(sc->sc_rxph);
		sc->sc_rxph = NULL;
	}

	if (sc->sc_txph) {
		FM_PORT_Free(sc->sc_txph);
		sc->sc_txph = NULL;
	}
}