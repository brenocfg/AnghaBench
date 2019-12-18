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
struct tegra124_car_softc {int /*<<< orphan*/  clkdom; } ;

/* Variables and functions */
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * periph_def ; 
 int periph_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgate_def ; 
 int pgate_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
tegra124_periph_clock(struct tegra124_car_softc *sc)
{
	int i, rv;

	for (i = 0; i <  nitems(periph_def); i++) {
		rv = periph_register(sc->clkdom, &periph_def[i]);
		if (rv != 0)
			panic("tegra124_periph_register failed");
	}
	for (i = 0; i <  nitems(pgate_def); i++) {
		rv = pgate_register(sc->clkdom, &pgate_def[i]);
		if (rv != 0)
			panic("tegra124_pgate_register failed");
	}

}