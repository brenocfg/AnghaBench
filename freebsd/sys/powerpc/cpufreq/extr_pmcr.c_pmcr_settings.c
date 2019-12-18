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
struct pmcr_softc {int dummy; } ;
struct cf_setting {int* spec; int /*<<< orphan*/  dev; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int E2BIG ; 
 int EINVAL ; 
 struct pmcr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 
 int npstates ; 
 int /*<<< orphan*/ * pstate_freqs ; 
 int* pstate_ids ; 

__attribute__((used)) static int
pmcr_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct pmcr_softc *sc;
	int i;

	sc = device_get_softc(dev);
	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < npstates)
		return (E2BIG);

	/* Return a list of valid settings for this driver. */
	memset(sets, CPUFREQ_VAL_UNKNOWN, sizeof(*sets) * npstates);

	for (i = 0; i < npstates; i++) {
		sets[i].freq = pstate_freqs[i];
		sets[i].spec[0] = pstate_ids[i];
		sets[i].spec[1] = i;
		sets[i].dev = dev;
	}
	*count = npstates;

	return (0);
}