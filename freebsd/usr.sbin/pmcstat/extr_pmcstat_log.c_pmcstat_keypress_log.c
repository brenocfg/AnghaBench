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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_4__ {size_t pa_plugin; int /*<<< orphan*/  pa_topmode; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pl_topkeypress ) (int,void*) ;int /*<<< orphan*/ * pl_name; int /*<<< orphan*/  (* pl_init ) () ;int /*<<< orphan*/ * pl_topdisplay; int /*<<< orphan*/  (* pl_shutdown ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PMCSTAT_TOP_ACCUM ; 
 int /*<<< orphan*/  PMCSTAT_TOP_DELTA ; 
 TYPE_2__ args ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newwin (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* plugins ; 
 int /*<<< orphan*/  pmcstat_changefilter () ; 
 int pmcstat_mergepmc ; 
 int /*<<< orphan*/  pmcstat_npmcs ; 
 int pmcstat_pause ; 
 int /*<<< orphan*/  pmcstat_pmcindex_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcstat_pmcinfilter ; 
 int /*<<< orphan*/  pmcstat_stats_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 (int,void*) ; 
 int wgetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

int
pmcstat_keypress_log(void)
{
	int c, ret = 0;
	WINDOW *w;

	w = newwin(1, 0, 1, 0);
	c = wgetch(w);
	wprintw(w, "Key: %c => ", c);
	switch (c) {
	case 'c':
		wprintw(w, "enter mode 'd' or 'a' => ");
		c = wgetch(w);
		if (c == 'd') {
			args.pa_topmode = PMCSTAT_TOP_DELTA;
			wprintw(w, "switching to delta mode");
		} else {
			args.pa_topmode = PMCSTAT_TOP_ACCUM;
			wprintw(w, "switching to accumulation mode");
		}
		break;
	case 'm':
		pmcstat_mergepmc = !pmcstat_mergepmc;
		/*
		 * Changing merge state require data reset.
		 */
		if (plugins[args.pa_plugin].pl_shutdown != NULL)
			plugins[args.pa_plugin].pl_shutdown(NULL);
		pmcstat_stats_reset(0);
		if (plugins[args.pa_plugin].pl_init != NULL)
			plugins[args.pa_plugin].pl_init();

		/* Update filter to be on a merge target. */
		pmcstat_changefilter();
		wprintw(w, "merge PMC %s", pmcstat_mergepmc ? "on" : "off");
		break;
	case 'n':
		/* Close current plugin. */
		if (plugins[args.pa_plugin].pl_shutdown != NULL)
			plugins[args.pa_plugin].pl_shutdown(NULL);

		/* Find next top display available. */
		do {
			args.pa_plugin++;
			if (plugins[args.pa_plugin].pl_name == NULL)
				args.pa_plugin = 0;
		} while (plugins[args.pa_plugin].pl_topdisplay == NULL);

		/* Open new plugin. */
		pmcstat_stats_reset(0);
		if (plugins[args.pa_plugin].pl_init != NULL)
			plugins[args.pa_plugin].pl_init();
		wprintw(w, "switching to plugin %s",
		    plugins[args.pa_plugin].pl_name);
		break;
	case 'p':
		pmcstat_pmcinfilter++;
		if (pmcstat_pmcinfilter >= pmcstat_npmcs)
			pmcstat_pmcinfilter = 0;
		pmcstat_changefilter();
		wprintw(w, "switching to PMC %s.%d",
		    pmcstat_pmcindex_to_name(pmcstat_pmcinfilter),
		    pmcstat_pmcinfilter);
		break;
	case ' ':
		pmcstat_pause = !pmcstat_pause;
		if (pmcstat_pause)
			wprintw(w, "pause => press space again to continue");
		break;
	case 'q':
		wprintw(w, "exiting...");
		ret = 1;
		break;
	default:
		if (plugins[args.pa_plugin].pl_topkeypress != NULL)
			if (plugins[args.pa_plugin].pl_topkeypress(c, (void *)w))
				ret = 1;
	}

	wrefresh(w);
	delwin(w);
	return ret;
}