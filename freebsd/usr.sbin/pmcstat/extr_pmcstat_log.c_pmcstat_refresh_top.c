#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmcstat_pmcrecord {double pr_samples; float pr_dubious_frames; int /*<<< orphan*/  pr_pmcname; } ;
typedef  int /*<<< orphan*/  pmcname ;
struct TYPE_4__ {size_t pa_plugin; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pl_topdisplay ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PMCSTAT_ATTROFF (int) ; 
 int /*<<< orphan*/  PMCSTAT_ATTRON (int) ; 
 int PMCSTAT_ATTRPERCENT (float) ; 
 int /*<<< orphan*/  PMCSTAT_PRINTBEGIN () ; 
 int /*<<< orphan*/  PMCSTAT_PRINTEND () ; 
 int /*<<< orphan*/  PMCSTAT_PRINTW (char*,...) ; 
 TYPE_2__ args ; 
 TYPE_1__* plugins ; 
 scalar_t__ pmcstat_mergepmc ; 
 scalar_t__ pmcstat_pause ; 
 struct pmcstat_pmcrecord* pmcstat_pmcindex_to_pmcr (int) ; 
 int pmcstat_pmcinfilter ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 
 double ps_samples_period ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void
pmcstat_refresh_top(void)
{
	int v_attrs;
	float v;
	char pmcname[40];
	struct pmcstat_pmcrecord *pmcpr;

	/* If in pause mode do not refresh display. */
	if (pmcstat_pause)
		return;

	/* Wait until PMC pop in the log. */
	pmcpr = pmcstat_pmcindex_to_pmcr(pmcstat_pmcinfilter);
	if (pmcpr == NULL)
		return;

	/* Format PMC name. */
	if (pmcstat_mergepmc)
		snprintf(pmcname, sizeof(pmcname), "[%s]",
		    pmcstat_string_unintern(pmcpr->pr_pmcname));
	else
		snprintf(pmcname, sizeof(pmcname), "%s.%d",
		    pmcstat_string_unintern(pmcpr->pr_pmcname),
		    pmcstat_pmcinfilter);

	/* Format samples count. */
	if (ps_samples_period > 0)
		v = (pmcpr->pr_samples * 100.0) / ps_samples_period;
	else
		v = 0.;
	v_attrs = PMCSTAT_ATTRPERCENT(v);

	PMCSTAT_PRINTBEGIN();
	PMCSTAT_PRINTW("PMC: %s Samples: %u ",
	    pmcname,
	    pmcpr->pr_samples);
	PMCSTAT_ATTRON(v_attrs);
	PMCSTAT_PRINTW("(%.1f%%) ", v);
	PMCSTAT_ATTROFF(v_attrs);
	PMCSTAT_PRINTW(", %u unresolved\n\n",
	    pmcpr->pr_dubious_frames);
	if (plugins[args.pa_plugin].pl_topdisplay != NULL)
		plugins[args.pa_plugin].pl_topdisplay();
	PMCSTAT_PRINTEND();
}