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
struct pmu_event_desc {int dummy; } ;
struct pmu_event {char const* alias; int /*<<< orphan*/ * event; } ;
struct pmc_op_pmcallocate {int pm_caps; int pm_ev; int /*<<< orphan*/  pm_md; } ;
typedef  scalar_t__ pmu_mfr_t ;

/* Variables and functions */
 int ENOENT ; 
 int PMC_CAP_READ ; 
 int PMC_CAP_WRITE ; 
 scalar_t__ PMU_INTEL ; 
 scalar_t__ PMU_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int pmc_pmu_amd_pmcallocate (char const*,struct pmc_op_pmcallocate*,struct pmu_event_desc*) ; 
 int pmc_pmu_intel_pmcallocate (char const*,struct pmc_op_pmcallocate*,struct pmu_event_desc*) ; 
 char* pmu_alias_get (char const*) ; 
 struct pmu_event* pmu_event_get (int /*<<< orphan*/ *,char const*,int*) ; 
 scalar_t__ pmu_events_mfr () ; 
 scalar_t__ pmu_parse_event (struct pmu_event_desc*,int /*<<< orphan*/ *) ; 

int
pmc_pmu_pmcallocate(const char *event_name, struct pmc_op_pmcallocate *pm)
{
	const struct pmu_event *pe;
	struct pmu_event_desc ped;
	pmu_mfr_t mfr;
	int idx = -1;

	if ((mfr = pmu_events_mfr()) == PMU_INVALID)
		return (ENOENT);

	bzero(&pm->pm_md, sizeof(pm->pm_md));
	pm->pm_caps |= (PMC_CAP_READ | PMC_CAP_WRITE);
	event_name = pmu_alias_get(event_name);
	if ((pe = pmu_event_get(NULL, event_name, &idx)) == NULL)
		return (ENOENT);
	if (pe->alias && (pe = pmu_event_get(NULL, pe->alias, &idx)) == NULL)
		return (ENOENT);
	assert(idx >= 0);
	pm->pm_ev = idx;

	if (pe->event == NULL)
		return (ENOENT);
	if (pmu_parse_event(&ped, pe->event))
		return (ENOENT);

	if (mfr == PMU_INTEL)
		return (pmc_pmu_intel_pmcallocate(event_name, pm, &ped));
	else
		return (pmc_pmu_amd_pmcallocate(event_name, pm, &ped));
}