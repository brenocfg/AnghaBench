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
 int /*<<< orphan*/ * super_mux_def ; 
 int super_mux_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
tegra124_super_mux_clock(struct tegra124_car_softc *sc)
{
	int i, rv;

	for (i = 0; i <  nitems(super_mux_def); i++) {
		rv = super_mux_register(sc->clkdom, &super_mux_def[i]);
		if (rv != 0)
			panic("super_mux_register failed");
	}

}