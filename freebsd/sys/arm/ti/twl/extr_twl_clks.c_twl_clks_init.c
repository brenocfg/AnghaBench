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
struct twl_clks_softc {int /*<<< orphan*/  sc_init_hook; int /*<<< orphan*/  sc_pdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct twl_clks_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_clocks ; 
 int /*<<< orphan*/  twl6030_clocks ; 
 int /*<<< orphan*/  twl_clks_add_clocks (struct twl_clks_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_4030 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6025 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6030 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
twl_clks_init(void *dev)
{
	struct twl_clks_softc *sc;

	sc = device_get_softc((device_t)dev);

	if (twl_is_4030(sc->sc_pdev))
		twl_clks_add_clocks(sc, twl4030_clocks);
	else if (twl_is_6030(sc->sc_pdev) || twl_is_6025(sc->sc_pdev))
		twl_clks_add_clocks(sc, twl6030_clocks);

	config_intrhook_disestablish(&sc->sc_init_hook);
}