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
struct pmcstat_target {int pt_pid; } ;
struct pmcstat_args {int pa_flags; int /*<<< orphan*/  pa_targets; } ;

/* Variables and functions */
 int FLAG_HAS_COMMANDLINE ; 
 struct pmcstat_target* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

int
pmc_util_get_pid(struct pmcstat_args *args)
{
	struct pmcstat_target *pt;

	assert(args->pa_flags & FLAG_HAS_COMMANDLINE);

	/*
	 * If a command line was specified, it would be the very first
	 * in the list, before any other processes specified by -t.
	 */
	pt = SLIST_FIRST(&args->pa_targets);
	return (pt->pt_pid);
}