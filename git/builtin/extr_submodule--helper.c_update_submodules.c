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
struct submodule_update_clone {int update_clone_nr; int /*<<< orphan*/ * update_clone; scalar_t__ quickstop; int /*<<< orphan*/  max_jobs; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_processes_parallel_tr2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct submodule_update_clone*,char*,char*) ; 
 int /*<<< orphan*/  update_clone_get_next_task ; 
 int /*<<< orphan*/  update_clone_start_failure ; 
 int /*<<< orphan*/  update_clone_task_finished ; 
 int /*<<< orphan*/  update_submodule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_submodules(struct submodule_update_clone *suc)
{
	int i;

	run_processes_parallel_tr2(suc->max_jobs, update_clone_get_next_task,
				   update_clone_start_failure,
				   update_clone_task_finished, suc, "submodule",
				   "parallel/update");

	/*
	 * We saved the output and put it out all at once now.
	 * That means:
	 * - the listener does not have to interleave their (checkout)
	 *   work with our fetching.  The writes involved in a
	 *   checkout involve more straightforward sequential I/O.
	 * - the listener can avoid doing any work if fetching failed.
	 */
	if (suc->quickstop)
		return 1;

	for (i = 0; i < suc->update_clone_nr; i++)
		update_submodule(&suc->update_clone[i]);

	return 0;
}