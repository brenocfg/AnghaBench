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
typedef  int register_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int EINVAL ; 
 int PMCR_LOWERPS_MASK ; 
 int PMCR_LOWERPS_SHIFT ; 
 int /*<<< orphan*/  SPR_PMCR ; 
 struct pmcr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int npstates ; 
 int /*<<< orphan*/ * pstate_freqs ; 
 int* pstate_ids ; 

__attribute__((used)) static int
pmcr_get(device_t dev, struct cf_setting *set)
{
	struct pmcr_softc *sc;
	register_t pmcr;
	int i, pstate;

	if (set == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	memset(set, CPUFREQ_VAL_UNKNOWN, sizeof(*set));

	pmcr = mfspr(SPR_PMCR);

	pstate = (pmcr & PMCR_LOWERPS_MASK) >> PMCR_LOWERPS_SHIFT;

	for (i = 0; i < npstates && pstate_ids[i] != pstate; i++)
		;

	if (i == npstates)
		return (EINVAL);

	set->spec[0] = pstate;
	set->spec[1] = i;
	set->freq = pstate_freqs[i];

	set->dev = dev;

	return (0);
}