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
typedef  int /*<<< orphan*/  tmparr ;
typedef  int /*<<< orphan*/  tmp ;
struct tegra124_pmc_softc {scalar_t__ suspend_mode; int cpu_good_time; int cpu_off_time; int core_osc_time; int core_pmu_time; int core_off_time; int lp0_vec_phys; void* lp0_vec_size; void* cpu_pwr_good_en; void* combined_req; void* sysclkreq_high; void* corereq_high; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 void* OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TEGRA_SUSPEND_LP0 ; 
 void* TEGRA_SUSPEND_LP1 ; 
 scalar_t__ TEGRA_SUSPEND_LP2 ; 
 void* TEGRA_SUSPEND_NONE ; 

__attribute__((used)) static int
tegra124_pmc_parse_fdt(struct tegra124_pmc_softc *sc, phandle_t node)
{
	int rv;
	uint32_t tmp;
	uint32_t tmparr[2];

	rv = OF_getencprop(node, "nvidia,suspend-mode", &tmp, sizeof(tmp));
	if (rv > 0) {
		switch (tmp) {
		case 0:
			sc->suspend_mode = TEGRA_SUSPEND_LP0;
			break;

		case 1:
			sc->suspend_mode = TEGRA_SUSPEND_LP1;
			break;

		case 2:
			sc->suspend_mode = TEGRA_SUSPEND_LP2;
			break;

		default:
			sc->suspend_mode = TEGRA_SUSPEND_NONE;
			break;
		}
	}

	rv = OF_getencprop(node, "nvidia,cpu-pwr-good-time", &tmp, sizeof(tmp));
	if (rv > 0) {
		sc->cpu_good_time = tmp;
		sc->suspend_mode = TEGRA_SUSPEND_NONE;
	}

	rv = OF_getencprop(node, "nvidia,cpu-pwr-off-time", &tmp, sizeof(tmp));
	if (rv > 0) {
		sc->cpu_off_time = tmp;
		sc->suspend_mode = TEGRA_SUSPEND_NONE;
	}

	rv = OF_getencprop(node, "nvidia,core-pwr-good-time", tmparr,
	    sizeof(tmparr));
	if (rv == sizeof(tmparr)) {
		sc->core_osc_time = tmparr[0];
		sc->core_pmu_time = tmparr[1];
		sc->suspend_mode = TEGRA_SUSPEND_NONE;
	}

	rv = OF_getencprop(node, "nvidia,core-pwr-off-time", &tmp, sizeof(tmp));
	if (rv > 0) {
		sc->core_off_time = tmp;
		sc->suspend_mode = TEGRA_SUSPEND_NONE;
	}

	sc->corereq_high =
	    OF_hasprop(node, "nvidia,core-power-req-active-high");
	sc->sysclkreq_high =
	    OF_hasprop(node, "nvidia,sys-clock-req-active-high");
	sc->combined_req =
	    OF_hasprop(node, "nvidia,combined-power-req");
	sc->cpu_pwr_good_en =
	    OF_hasprop(node, "nvidia,cpu-pwr-good-en");

	rv = OF_getencprop(node, "nvidia,lp0-vec", tmparr, sizeof(tmparr));
	if (rv == sizeof(tmparr)) {

		sc->lp0_vec_phys = tmparr[0];
		sc->core_pmu_time = tmparr[1];
		sc->lp0_vec_size = TEGRA_SUSPEND_NONE;
		if (sc->suspend_mode == TEGRA_SUSPEND_LP0)
			sc->suspend_mode = TEGRA_SUSPEND_LP1;
	}
	return 0;
}