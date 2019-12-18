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
typedef  int u64 ;

/* Variables and functions */
 int MAX_ALT ; 
 int PM_PMCSEL_MSK ; 
 int PM_PMC_MSK ; 
 int PM_PMC_MSKS ; 
 int PM_PMC_SH ; 
 unsigned int PPMU_LIMITED_PMC_OK ; 
 unsigned int PPMU_LIMITED_PMC_REQD ; 
 unsigned int PPMU_ONLY_COUNT_RUN ; 
 int** event_alternatives ; 
 int find_alternatives_list (int) ; 
 int p6_limited_pmc_event (int) ; 

__attribute__((used)) static int p6_get_alternatives(u64 event, unsigned int flags, u64 alt[])
{
	int i, j, nlim;
	unsigned int psel, pmc;
	unsigned int nalt = 1;
	u64 aevent;

	alt[0] = event;
	nlim = p6_limited_pmc_event(event);

	/* check the alternatives table */
	i = find_alternatives_list(event);
	if (i >= 0) {
		/* copy out alternatives from list */
		for (j = 0; j < MAX_ALT; ++j) {
			aevent = event_alternatives[i][j];
			if (!aevent)
				break;
			if (aevent != event)
				alt[nalt++] = aevent;
			nlim += p6_limited_pmc_event(aevent);
		}

	} else {
		/* Check for alternative ways of computing sum events */
		/* PMCSEL 0x32 counter N == PMCSEL 0x34 counter 5-N */
		psel = event & (PM_PMCSEL_MSK & ~1);	/* ignore edge bit */
		pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc && (psel == 0x32 || psel == 0x34))
			alt[nalt++] = ((event ^ 0x6) & ~PM_PMC_MSKS) |
				((5 - pmc) << PM_PMC_SH);

		/* PMCSEL 0x38 counter N == PMCSEL 0x3a counter N+/-2 */
		if (pmc && (psel == 0x38 || psel == 0x3a))
			alt[nalt++] = ((event ^ 0x2) & ~PM_PMC_MSKS) |
				((pmc > 2? pmc - 2: pmc + 2) << PM_PMC_SH);
	}

	if (flags & PPMU_ONLY_COUNT_RUN) {
		/*
		 * We're only counting in RUN state,
		 * so PM_CYC is equivalent to PM_RUN_CYC,
		 * PM_INST_CMPL === PM_RUN_INST_CMPL, PM_PURR === PM_RUN_PURR.
		 * This doesn't include alternatives that don't provide
		 * any extra flexibility in assigning PMCs (e.g.
		 * 0x10000a for PM_RUN_CYC vs. 0x1e for PM_CYC).
		 * Note that even with these additional alternatives
		 * we never end up with more than 4 alternatives for any event.
		 */
		j = nalt;
		for (i = 0; i < nalt; ++i) {
			switch (alt[i]) {
			case 0x1e:	/* PM_CYC */
				alt[j++] = 0x600005;	/* PM_RUN_CYC */
				++nlim;
				break;
			case 0x10000a:	/* PM_RUN_CYC */
				alt[j++] = 0x1e;	/* PM_CYC */
				break;
			case 2:		/* PM_INST_CMPL */
				alt[j++] = 0x500009;	/* PM_RUN_INST_CMPL */
				++nlim;
				break;
			case 0x500009:	/* PM_RUN_INST_CMPL */
				alt[j++] = 2;		/* PM_INST_CMPL */
				break;
			case 0x10000e:	/* PM_PURR */
				alt[j++] = 0x4000f4;	/* PM_RUN_PURR */
				break;
			case 0x4000f4:	/* PM_RUN_PURR */
				alt[j++] = 0x10000e;	/* PM_PURR */
				break;
			}
		}
		nalt = j;
	}

	if (!(flags & PPMU_LIMITED_PMC_OK) && nlim) {
		/* remove the limited PMC events */
		j = 0;
		for (i = 0; i < nalt; ++i) {
			if (!p6_limited_pmc_event(alt[i])) {
				alt[j] = alt[i];
				++j;
			}
		}
		nalt = j;
	} else if ((flags & PPMU_LIMITED_PMC_REQD) && nlim < nalt) {
		/* remove all but the limited PMC events */
		j = 0;
		for (i = 0; i < nalt; ++i) {
			if (p6_limited_pmc_event(alt[i])) {
				alt[j] = alt[i];
				++j;
			}
		}
		nalt = j;
	}

	return nalt;
}