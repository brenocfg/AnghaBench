#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra124_cpufreq_softc {int nspeed_points; int cpu_max_freq; int /*<<< orphan*/  latency; TYPE_1__* speed_points; } ;
struct cf_setting {int freq; int volts; int /*<<< orphan*/  dev; int /*<<< orphan*/  lat; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int freq; int uvolt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int EINVAL ; 
 struct tegra124_cpufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int
tegra124_cpufreq_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct tegra124_cpufreq_softc *sc;
	int i, j, max_cnt;

	if (sets == NULL || count == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);
	memset(sets, CPUFREQ_VAL_UNKNOWN, sizeof(*sets) * (*count));

	max_cnt = min(sc->nspeed_points, *count);
	for (i = 0, j = sc->nspeed_points - 1; j >= 0; j--) {
		if (sc->cpu_max_freq < sc->speed_points[j].freq)
			continue;
		sets[i].freq = sc->speed_points[j].freq / 1000000;
		sets[i].volts = sc->speed_points[j].uvolt / 1000;
		sets[i].lat = sc->latency;
		sets[i].dev = dev;
		i++;
	}
	*count = i;

	return (0);
}