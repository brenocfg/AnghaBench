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
struct repository {int dummy; } ;
struct fetch_task {int free_sub; scalar_t__ sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct fetch_task*) ; 
 scalar_t__ get_non_gitmodules_submodule (char const*) ; 
 int /*<<< orphan*/  memset (struct fetch_task*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  null_oid ; 
 scalar_t__ submodule_from_path (struct repository*,int /*<<< orphan*/ *,char const*) ; 
 struct fetch_task* xmalloc (int) ; 

__attribute__((used)) static struct fetch_task *fetch_task_create(struct repository *r,
					    const char *path)
{
	struct fetch_task *task = xmalloc(sizeof(*task));
	memset(task, 0, sizeof(*task));

	task->sub = submodule_from_path(r, &null_oid, path);
	if (!task->sub) {
		/*
		 * No entry in .gitmodules? Technically not a submodule,
		 * but historically we supported repositories that happen to be
		 * in-place where a gitlink is. Keep supporting them.
		 */
		task->sub = get_non_gitmodules_submodule(path);
		if (!task->sub) {
			free(task);
			return NULL;
		}

		task->free_sub = 1;
	}

	return task;
}