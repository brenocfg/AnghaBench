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
struct submodule_parallel_fetch {int result; int oid_fetch_tasks_nr; struct fetch_task** oid_fetch_tasks; int /*<<< orphan*/  oid_fetch_tasks_alloc; int /*<<< orphan*/  changed_submodule_names; } ;
struct string_list_item {struct oid_array* util; } ;
struct strbuf {int dummy; } ;
struct oid_array {scalar_t__ nr; } ;
struct fetch_task {struct oid_array* commits; int /*<<< orphan*/  repo; TYPE_1__* sub; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct fetch_task**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  commit_missing_in_sub ; 
 int /*<<< orphan*/  fetch_task_release (struct fetch_task*) ; 
 int /*<<< orphan*/  oid_array_filter (struct oid_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct string_list_item* string_list_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fetch_finish(int retvalue, struct strbuf *err,
			void *cb, void *task_cb)
{
	struct submodule_parallel_fetch *spf = cb;
	struct fetch_task *task = task_cb;

	struct string_list_item *it;
	struct oid_array *commits;

	if (retvalue)
		/*
		 * NEEDSWORK: This indicates that the overall fetch
		 * failed, even though there may be a subsequent fetch
		 * by commit hash that might work. It may be a good
		 * idea to not indicate failure in this case, and only
		 * indicate failure if the subsequent fetch fails.
		 */
		spf->result = 1;

	if (!task || !task->sub)
		BUG("callback cookie bogus");

	/* Is this the second time we process this submodule? */
	if (task->commits)
		goto out;

	it = string_list_lookup(&spf->changed_submodule_names, task->sub->name);
	if (!it)
		/* Could be an unchanged submodule, not contained in the list */
		goto out;

	commits = it->util;
	oid_array_filter(commits,
			 commit_missing_in_sub,
			 task->repo);

	/* Are there commits we want, but do not exist? */
	if (commits->nr) {
		task->commits = commits;
		ALLOC_GROW(spf->oid_fetch_tasks,
			   spf->oid_fetch_tasks_nr + 1,
			   spf->oid_fetch_tasks_alloc);
		spf->oid_fetch_tasks[spf->oid_fetch_tasks_nr] = task;
		spf->oid_fetch_tasks_nr++;
		return 0;
	}

out:
	fetch_task_release(task);

	return 0;
}