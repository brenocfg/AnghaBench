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
struct tegra124_pmc_softc {int /*<<< orphan*/  dev; } ;
typedef  enum tegra_powergate_id { ____Placeholder_tegra_powergate_id } tegra_powergate_id ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct tegra124_pmc_softc* tegra124_pmc_get_sc () ; 
 int tegra124_pmc_set_powergate (struct tegra124_pmc_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_is_powered (int) ; 

int
tegra_powergate_power_off(enum tegra_powergate_id id)
{
	struct tegra124_pmc_softc *sc;
	int rv, i;

	sc = tegra124_pmc_get_sc();

	rv = tegra124_pmc_set_powergate(sc, id, 0);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot set powergate: %d\n", id);
		return (rv);
	}
	for (i = 100; i > 0; i--) {
		if (!tegra_powergate_is_powered(id))
			break;
		DELAY(1);
	}
	if (i <= 0)
		device_printf(sc->dev, "Timeout when waiting on power off\n");

	return (rv);
}