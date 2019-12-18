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
struct pmcpl_ct_sample {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCSTAT_PRINTW (char*,...) ; 
 int /*<<< orphan*/  pmcpl_ct_node_cleartag () ; 
 scalar_t__ pmcpl_ct_node_dumptop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmcpl_ct_sample*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pmcpl_ct_node_printtop (struct pmcpl_ct_sample*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmcpl_ct_root ; 
 int /*<<< orphan*/  pmcpl_ct_samples_free (struct pmcpl_ct_sample*) ; 
 int /*<<< orphan*/  pmcpl_ct_samples_root (struct pmcpl_ct_sample*) ; 
 int /*<<< orphan*/ *** pmcpl_ct_topscreen ; 
 scalar_t__ pmcstat_displayheight ; 
 int /*<<< orphan*/  pmcstat_pmcinfilter ; 

void
pmcpl_ct_topdisplay(void)
{
	int y;
	struct pmcpl_ct_sample r, *rsamples;

	rsamples = &r;
	pmcpl_ct_samples_root(rsamples);
	pmcpl_ct_node_cleartag();

	PMCSTAT_PRINTW("%5.5s %s\n", "%SAMP", "CALLTREE");

	y = 0;
	if (pmcpl_ct_node_dumptop(pmcstat_pmcinfilter,
	    pmcpl_ct_root, rsamples, 0, &y))
		PMCSTAT_PRINTW("...\n");
	pmcpl_ct_topscreen[1][y] = NULL;

	pmcpl_ct_node_printtop(rsamples,
	    pmcstat_pmcinfilter, pmcstat_displayheight - 2);

	pmcpl_ct_samples_free(rsamples);
}