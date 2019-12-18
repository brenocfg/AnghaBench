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
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  enum tegra_powergate_id { ____Placeholder_tegra_powergate_id } tegra_powergate_id ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_assert (int /*<<< orphan*/ ) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 struct tegra124_pmc_softc* tegra124_pmc_get_sc () ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int) ; 
 int tegra_powergate_power_on (int) ; 
 int tegra_powergate_remove_clamping (int) ; 

int
tegra_powergate_sequence_power_up(enum tegra_powergate_id id, clk_t clk,
    hwreset_t rst)
{
	struct tegra124_pmc_softc *sc;
	int rv;

	sc = tegra124_pmc_get_sc();

	rv = hwreset_assert(rst);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert reset\n");
		return (rv);
	}

	rv = clk_stop(clk);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot stop clock\n");
		goto clk_fail;
	}

	rv = tegra_powergate_power_on(id);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot power on powergate\n");
		goto clk_fail;
	}

	rv = clk_enable(clk);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable clock\n");
		goto clk_fail;
	}
	DELAY(20);

	rv = tegra_powergate_remove_clamping(id);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot remove clamping\n");
		goto fail;
	}
	rv = hwreset_deassert(rst);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot unreset reset\n");
		goto fail;
	}
	return 0;

fail:
	clk_disable(clk);
clk_fail:
	hwreset_assert(rst);
	tegra_powergate_power_off(id);
	return (rv);
}