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
typedef  int uint64_t ;
struct tegra124_cpufreq_softc {int cpu_max_freq; } ;
struct cf_setting {scalar_t__ freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int cpufreq_lowest_freq ; 
 struct tegra124_cpufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int set_cpu_freq (struct tegra124_cpufreq_softc*,int) ; 

__attribute__((used)) static int
tegra124_cpufreq_set(device_t dev, const struct cf_setting *cf)
{
	struct tegra124_cpufreq_softc *sc;
	uint64_t freq;
	int rv;

	if (cf == NULL || cf->freq < 0)
		return (EINVAL);

	sc = device_get_softc(dev);

	freq = cf->freq;
	if (freq < cpufreq_lowest_freq)
		freq = cpufreq_lowest_freq;
	freq *= 1000000;
	if (freq >= sc->cpu_max_freq)
		freq = sc->cpu_max_freq;
	rv = set_cpu_freq(sc, freq);

	return (rv);
}