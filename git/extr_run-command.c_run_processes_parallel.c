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
struct parallel_processes {int shutdown; scalar_t__ nr_processes; scalar_t__ max_processes; } ;
typedef  int /*<<< orphan*/  start_failure_fn ;
typedef  int /*<<< orphan*/  get_next_task_fn ;

/* Variables and functions */
 int /*<<< orphan*/  kill_children (struct parallel_processes*,int) ; 
 int /*<<< orphan*/  pp_buffer_stderr (struct parallel_processes*,int) ; 
 int /*<<< orphan*/  pp_cleanup (struct parallel_processes*) ; 
 int pp_collect_finished (struct parallel_processes*) ; 
 int /*<<< orphan*/  pp_init (struct parallel_processes*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pp_output (struct parallel_processes*) ; 
 int pp_start_one (struct parallel_processes*) ; 

int run_processes_parallel(int n,
			   get_next_task_fn get_next_task,
			   start_failure_fn start_failure,
			   task_finished_fn task_finished,
			   void *pp_cb)
{
	int i, code;
	int output_timeout = 100;
	int spawn_cap = 4;
	struct parallel_processes pp;

	pp_init(&pp, n, get_next_task, start_failure, task_finished, pp_cb);
	while (1) {
		for (i = 0;
		    i < spawn_cap && !pp.shutdown &&
		    pp.nr_processes < pp.max_processes;
		    i++) {
			code = pp_start_one(&pp);
			if (!code)
				continue;
			if (code < 0) {
				pp.shutdown = 1;
				kill_children(&pp, -code);
			}
			break;
		}
		if (!pp.nr_processes)
			break;
		pp_buffer_stderr(&pp, output_timeout);
		pp_output(&pp);
		code = pp_collect_finished(&pp);
		if (code) {
			pp.shutdown = 1;
			if (code < 0)
				kill_children(&pp, -code);
		}
	}

	pp_cleanup(&pp);
	return 0;
}