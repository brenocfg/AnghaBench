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
struct cpufreq_dt_softc {int nopp; int /*<<< orphan*/ * opp; } ;
struct cf_setting {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_dt_opp_to_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cf_setting*) ; 
 struct cpufreq_dt_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpufreq_dt_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct cpufreq_dt_softc *sc;
	ssize_t n;

	DEBUG(dev, "cpufreq_dt_settings\n");
	if (sets == NULL || count == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);

	if (*count < sc->nopp) {
		*count = (int)sc->nopp;
		return (E2BIG);
	}

	for (n = 0; n < sc->nopp; n++)
		cpufreq_dt_opp_to_setting(dev, &sc->opp[n], &sets[n]);

	*count = (int)sc->nopp;

	return (0);
}