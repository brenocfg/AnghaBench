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
struct pmcstat_pmcrecord {struct pmcstat_pmcrecord* pr_merge; } ;

/* Variables and functions */
 scalar_t__ pmcstat_mergepmc ; 
 int pmcstat_npmcs ; 
 struct pmcstat_pmcrecord* pmcstat_pmcindex_to_pmcr (int) ; 
 int pmcstat_pmcinfilter ; 

__attribute__((used)) static void
pmcstat_changefilter(void)
{
	int pmcin;
	struct pmcstat_pmcrecord *pmcr;

	/*
	 * Find the next merge target.
	 */
	if (pmcstat_mergepmc) {
		pmcin = pmcstat_pmcinfilter;

		do {
			pmcr = pmcstat_pmcindex_to_pmcr(pmcstat_pmcinfilter);
			if (pmcr == NULL || pmcr == pmcr->pr_merge)
				break;

			pmcstat_pmcinfilter++;
			if (pmcstat_pmcinfilter >= pmcstat_npmcs)
				pmcstat_pmcinfilter = 0;

		} while (pmcstat_pmcinfilter != pmcin);
	}
}