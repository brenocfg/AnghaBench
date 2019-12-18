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
typedef  scalar_t__ task_finished_fn ;
struct parallel_processes {int max_processes; TYPE_2__* pfd; TYPE_1__* children; int /*<<< orphan*/  buffered_output; scalar_t__ shutdown; scalar_t__ output_owner; scalar_t__ nr_processes; scalar_t__ task_finished; scalar_t__ start_failure; scalar_t__ get_next_task; void* data; } ;
typedef  scalar_t__ start_failure_fn ;
typedef  scalar_t__ get_next_task_fn ;
struct TYPE_4__ {int events; int fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  process; int /*<<< orphan*/  err; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int POLLHUP ; 
 int POLLIN ; 
 int /*<<< orphan*/  child_process_init (int /*<<< orphan*/ *) ; 
 scalar_t__ default_start_failure ; 
 scalar_t__ default_task_finished ; 
 int /*<<< orphan*/  handle_children_on_signal ; 
 int online_cpus () ; 
 struct parallel_processes* pp_for_signal ; 
 int /*<<< orphan*/  sigchain_push_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_printf (char*,int) ; 
 void* xcalloc (int,int) ; 

__attribute__((used)) static void pp_init(struct parallel_processes *pp,
		    int n,
		    get_next_task_fn get_next_task,
		    start_failure_fn start_failure,
		    task_finished_fn task_finished,
		    void *data)
{
	int i;

	if (n < 1)
		n = online_cpus();

	pp->max_processes = n;

	trace_printf("run_processes_parallel: preparing to run up to %d tasks", n);

	pp->data = data;
	if (!get_next_task)
		BUG("you need to specify a get_next_task function");
	pp->get_next_task = get_next_task;

	pp->start_failure = start_failure ? start_failure : default_start_failure;
	pp->task_finished = task_finished ? task_finished : default_task_finished;

	pp->nr_processes = 0;
	pp->output_owner = 0;
	pp->shutdown = 0;
	pp->children = xcalloc(n, sizeof(*pp->children));
	pp->pfd = xcalloc(n, sizeof(*pp->pfd));
	strbuf_init(&pp->buffered_output, 0);

	for (i = 0; i < n; i++) {
		strbuf_init(&pp->children[i].err, 0);
		child_process_init(&pp->children[i].process);
		pp->pfd[i].events = POLLIN | POLLHUP;
		pp->pfd[i].fd = -1;
	}

	pp_for_signal = pp;
	sigchain_push_common(handle_children_on_signal);
}