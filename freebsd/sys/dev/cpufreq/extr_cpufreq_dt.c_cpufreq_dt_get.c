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
typedef  int /*<<< orphan*/  uint64_t ;
struct cpufreq_dt_softc {int /*<<< orphan*/  clk; } ;
struct cpufreq_dt_opp {int dummy; } ;
struct cf_setting {int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int ENOENT ; 
 int ENXIO ; 
 scalar_t__ clk_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cpufreq_dt_opp* cpufreq_dt_find_opp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_dt_opp_to_setting (int /*<<< orphan*/ ,struct cpufreq_dt_opp const*,struct cf_setting*) ; 
 struct cpufreq_dt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cpufreq_dt_get(device_t dev, struct cf_setting *set)
{
	struct cpufreq_dt_softc *sc;
	const struct cpufreq_dt_opp *opp;
	uint64_t freq;

	sc = device_get_softc(dev);

	DEBUG(dev, "cpufreq_dt_get\n");
	if (clk_get_freq(sc->clk, &freq) != 0)
		return (ENXIO);

	opp = cpufreq_dt_find_opp(dev, freq);
	if (opp == NULL) {
		device_printf(dev, "Can't find the current freq in opp\n");
		return (ENOENT);
	}

	cpufreq_dt_opp_to_setting(dev, opp, set);

	DEBUG(dev, "Current freq %dMhz\n", set->freq);
	return (0);
}