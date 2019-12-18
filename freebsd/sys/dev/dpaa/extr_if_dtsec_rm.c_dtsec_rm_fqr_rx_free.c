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
struct dtsec_softc {scalar_t__ sc_rx_fqr; } ;

/* Variables and functions */
 int /*<<< orphan*/  qman_fqr_free (scalar_t__) ; 

void
dtsec_rm_fqr_rx_free(struct dtsec_softc *sc)
{

	if (sc->sc_rx_fqr)
		qman_fqr_free(sc->sc_rx_fqr);
}