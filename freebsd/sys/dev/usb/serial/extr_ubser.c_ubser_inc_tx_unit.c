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
struct ubser_softc {scalar_t__ sc_curr_tx_unit; scalar_t__ sc_numser; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
ubser_inc_tx_unit(struct ubser_softc *sc)
{
	sc->sc_curr_tx_unit++;
	if (sc->sc_curr_tx_unit >= sc->sc_numser) {
		sc->sc_curr_tx_unit = 0;
	}
}