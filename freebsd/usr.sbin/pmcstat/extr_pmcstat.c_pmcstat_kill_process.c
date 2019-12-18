#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmcstat_target {int /*<<< orphan*/  pt_pid; } ;
struct TYPE_2__ {int pa_flags; int /*<<< orphan*/  pa_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int FLAG_HAS_COMMANDLINE ; 
 int /*<<< orphan*/  SIGINT ; 
 struct pmcstat_target* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__ args ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmcstat_kill_process(void)
{
	struct pmcstat_target *pt;

	assert(args.pa_flags & FLAG_HAS_COMMANDLINE);

	/*
	 * If a command line was specified, it would be the very first
	 * in the list, before any other processes specified by -t.
	 */
	pt = SLIST_FIRST(&args.pa_targets);
	assert(pt != NULL);

	if (kill(pt->pt_pid, SIGINT) != 0)
		err(EX_OSERR, "ERROR: cannot signal child process");
}