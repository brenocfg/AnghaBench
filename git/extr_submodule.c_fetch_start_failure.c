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
struct submodule_parallel_fetch {int result; } ;
struct strbuf {int dummy; } ;
struct fetch_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fetch_task_release (struct fetch_task*) ; 

__attribute__((used)) static int fetch_start_failure(struct strbuf *err,
			       void *cb, void *task_cb)
{
	struct submodule_parallel_fetch *spf = cb;
	struct fetch_task *task = task_cb;

	spf->result = 1;

	fetch_task_release(task);
	return 0;
}