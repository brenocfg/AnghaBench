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
struct tegra124_cpufreq_softc {int /*<<< orphan*/  latency; TYPE_1__* act_speed_point; } ;
struct cf_setting {int freq; int volts; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lat; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int freq; int uvolt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int EINVAL ; 
 struct tegra124_cpufreq_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tegra124_cpufreq_get(device_t dev, struct cf_setting *cf)
{
	struct tegra124_cpufreq_softc *sc;

	if (cf == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);
	memset(cf, CPUFREQ_VAL_UNKNOWN, sizeof(*cf));
	cf->dev = NULL;
	cf->freq = sc->act_speed_point->freq / 1000000;
	cf->volts = sc->act_speed_point->uvolt / 1000;
	/* Transition latency in us. */
	cf->lat = sc->latency;
	/* Driver providing this setting. */
	cf->dev = dev;

	return (0);
}