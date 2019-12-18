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
struct tegra124_car_softc {int /*<<< orphan*/ * clkdom; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * clkdom_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_dump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clkdom_finit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clkdom_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clkdom_xlock (int /*<<< orphan*/ *) ; 
 struct tegra124_car_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_divs (struct tegra124_car_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_fixeds (struct tegra124_car_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_gates (struct tegra124_car_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_muxes (struct tegra124_car_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  postinit_clock (struct tegra124_car_softc*) ; 
 int /*<<< orphan*/  tegra124_div_clks ; 
 int /*<<< orphan*/  tegra124_fixed_clks ; 
 int /*<<< orphan*/  tegra124_gate_clks ; 
 int /*<<< orphan*/  tegra124_init_plls (struct tegra124_car_softc*) ; 
 int /*<<< orphan*/  tegra124_mux_clks ; 
 int /*<<< orphan*/  tegra124_periph_clock (struct tegra124_car_softc*) ; 
 int /*<<< orphan*/  tegra124_super_mux_clock (struct tegra124_car_softc*) ; 

__attribute__((used)) static void
register_clocks(device_t dev)
{
	struct tegra124_car_softc *sc;

	sc = device_get_softc(dev);
	sc->clkdom = clkdom_create(dev);
	if (sc->clkdom == NULL)
		panic("clkdom == NULL");

	tegra124_init_plls(sc);
	init_fixeds(sc, tegra124_fixed_clks, nitems(tegra124_fixed_clks));
	init_muxes(sc, tegra124_mux_clks, nitems(tegra124_mux_clks));
	init_divs(sc, tegra124_div_clks, nitems(tegra124_div_clks));
	init_gates(sc, tegra124_gate_clks, nitems(tegra124_gate_clks));
	tegra124_periph_clock(sc);
	tegra124_super_mux_clock(sc);
	clkdom_finit(sc->clkdom);
	clkdom_xlock(sc->clkdom);
	postinit_clock(sc);
	clkdom_unlock(sc->clkdom);
	if (bootverbose)
		clkdom_dump(sc->clkdom);
}