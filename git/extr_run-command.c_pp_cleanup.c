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
struct parallel_processes {int max_processes; int /*<<< orphan*/  buffered_output; TYPE_1__* pfd; TYPE_1__* children; } ;
struct TYPE_2__ {int /*<<< orphan*/  process; int /*<<< orphan*/  err; } ;

/* Variables and functions */
 int /*<<< orphan*/  child_process_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  sigchain_pop_common () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_printf (char*) ; 

__attribute__((used)) static void pp_cleanup(struct parallel_processes *pp)
{
	int i;

	trace_printf("run_processes_parallel: done");
	for (i = 0; i < pp->max_processes; i++) {
		strbuf_release(&pp->children[i].err);
		child_process_clear(&pp->children[i].process);
	}

	free(pp->children);
	free(pp->pfd);

	/*
	 * When get_next_task added messages to the buffer in its last
	 * iteration, the buffered output is non empty.
	 */
	strbuf_write(&pp->buffered_output, stderr);
	strbuf_release(&pp->buffered_output);

	sigchain_pop_common();
}