#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pa_flags; } ;

/* Variables and functions */
 int FLAG_DO_PRINT ; 
 TYPE_1__ args ; 
 int /*<<< orphan*/  plugins ; 
 int pmcstat_analyze_log (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcstat_kernproc ; 
 int /*<<< orphan*/  pmcstat_mergepmc ; 
 int /*<<< orphan*/  pmcstat_npmcs ; 
 int pmcstat_print_log () ; 
 int /*<<< orphan*/  pmcstat_stats ; 
 int /*<<< orphan*/  ps_samples_period ; 

int
pmcstat_process_log(void)
{

	/*
	 * If analysis has not been asked for, just print the log to
	 * the current output file.
	 */
	if (args.pa_flags & FLAG_DO_PRINT)
		return (pmcstat_print_log());
	else
		return (pmcstat_analyze_log(&args, plugins, &pmcstat_stats, pmcstat_kernproc,
		    pmcstat_mergepmc, &pmcstat_npmcs, &ps_samples_period));
}