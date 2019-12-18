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
typedef  int uint32_t ;
struct tegra124_pmc_softc {int /*<<< orphan*/  dev; } ;
typedef  enum tegra_powergate_id { ____Placeholder_tegra_powergate_id } tegra_powergate_id ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PMC_LOCK (struct tegra124_pmc_softc*) ; 
 int /*<<< orphan*/  PMC_PWRGATE_STATUS ; 
 int PMC_PWRGATE_STATUS_PARTID (int) ; 
 int /*<<< orphan*/  PMC_PWRGATE_TOGGLE ; 
 int PMC_PWRGATE_TOGGLE_PARTID (int) ; 
 int PMC_PWRGATE_TOGGLE_START ; 
 int /*<<< orphan*/  PMC_UNLOCK (struct tegra124_pmc_softc*) ; 
 int RD4 (struct tegra124_pmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct tegra124_pmc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
tegra124_pmc_set_powergate(struct tegra124_pmc_softc *sc,
    enum tegra_powergate_id id, int ena)
{
	uint32_t reg;
	int i;

	PMC_LOCK(sc);

	reg = RD4(sc, PMC_PWRGATE_STATUS) & PMC_PWRGATE_STATUS_PARTID(id);
	if (((reg != 0) && ena) || ((reg == 0) && !ena)) {
		PMC_UNLOCK(sc);
		return (0);
	}

	for (i = 100; i > 0; i--) {
		reg = RD4(sc, PMC_PWRGATE_TOGGLE);
		if ((reg & PMC_PWRGATE_TOGGLE_START) == 0)
			break;
		DELAY(1);
	}
	if (i <= 0)
		device_printf(sc->dev,
		    "Timeout when waiting for TOGGLE_START\n");

	WR4(sc, PMC_PWRGATE_TOGGLE,
	    PMC_PWRGATE_TOGGLE_START | PMC_PWRGATE_TOGGLE_PARTID(id));

	for (i = 100; i > 0; i--) {
		reg = RD4(sc, PMC_PWRGATE_TOGGLE);
		if ((reg & PMC_PWRGATE_TOGGLE_START) == 0)
			break;
		DELAY(1);
	}
	if (i <= 0)
		device_printf(sc->dev,
		    "Timeout when waiting for TOGGLE_START\n");
		PMC_UNLOCK(sc);
	return (0);
}