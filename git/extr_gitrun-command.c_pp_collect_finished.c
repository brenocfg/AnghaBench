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
struct parallel_processes {int max_processes; scalar_t__ nr_processes; int (* task_finished ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int output_owner; TYPE_2__* children; int /*<<< orphan*/  buffered_output; TYPE_1__* pfd; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  err; int /*<<< orphan*/  process; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int fd; } ;

/* Variables and functions */
 scalar_t__ GIT_CP_FREE ; 
 scalar_t__ GIT_CP_WAIT_CLEANUP ; 
 scalar_t__ GIT_CP_WORKING ; 
 int /*<<< orphan*/  child_process_init (int /*<<< orphan*/ *) ; 
 int finish_command (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pp_collect_finished(struct parallel_processes *pp)
{
	int i, code;
	int n = pp->max_processes;
	int result = 0;

	while (pp->nr_processes > 0) {
		for (i = 0; i < pp->max_processes; i++)
			if (pp->children[i].state == GIT_CP_WAIT_CLEANUP)
				break;
		if (i == pp->max_processes)
			break;

		code = finish_command(&pp->children[i].process);

		code = pp->task_finished(code,
					 &pp->children[i].err, pp->data,
					 pp->children[i].data);

		if (code)
			result = code;
		if (code < 0)
			break;

		pp->nr_processes--;
		pp->children[i].state = GIT_CP_FREE;
		pp->pfd[i].fd = -1;
		child_process_init(&pp->children[i].process);

		if (i != pp->output_owner) {
			strbuf_addbuf(&pp->buffered_output, &pp->children[i].err);
			strbuf_reset(&pp->children[i].err);
		} else {
			strbuf_write(&pp->children[i].err, stderr);
			strbuf_reset(&pp->children[i].err);

			/* Output all other finished child processes */
			strbuf_write(&pp->buffered_output, stderr);
			strbuf_reset(&pp->buffered_output);

			/*
			 * Pick next process to output live.
			 * NEEDSWORK:
			 * For now we pick it randomly by doing a round
			 * robin. Later we may want to pick the one with
			 * the most output or the longest or shortest
			 * running process time.
			 */
			for (i = 0; i < n; i++)
				if (pp->children[(pp->output_owner + i) % n].state == GIT_CP_WORKING)
					break;
			pp->output_owner = (pp->output_owner + i) % n;
		}
	}
	return result;
}