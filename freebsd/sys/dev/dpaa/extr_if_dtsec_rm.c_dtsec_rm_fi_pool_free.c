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
struct dtsec_softc {int /*<<< orphan*/ * sc_fi_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ *) ; 

void
dtsec_rm_fi_pool_free(struct dtsec_softc *sc)
{

	if (sc->sc_fi_zone != NULL)
		uma_zdestroy(sc->sc_fi_zone);
}