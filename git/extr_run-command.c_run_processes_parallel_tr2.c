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
typedef  int /*<<< orphan*/  task_finished_fn ;
typedef  int /*<<< orphan*/  start_failure_fn ;
typedef  int /*<<< orphan*/  get_next_task_fn ;

/* Variables and functions */
 int online_cpus () ; 
 int run_processes_parallel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  trace2_region_enter_printf (char const*,char const*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  trace2_region_leave (char const*,char const*,int /*<<< orphan*/ *) ; 

int run_processes_parallel_tr2(int n, get_next_task_fn get_next_task,
			       start_failure_fn start_failure,
			       task_finished_fn task_finished, void *pp_cb,
			       const char *tr2_category, const char *tr2_label)
{
	int result;

	trace2_region_enter_printf(tr2_category, tr2_label, NULL, "max:%d",
				   ((n < 1) ? online_cpus() : n));

	result = run_processes_parallel(n, get_next_task, start_failure,
					task_finished, pp_cb);

	trace2_region_leave(tr2_category, tr2_label, NULL);

	return result;
}