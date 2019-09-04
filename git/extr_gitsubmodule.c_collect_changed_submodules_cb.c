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
struct submodule {char* name; } ;
struct string_list {int dummy; } ;
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_options {int dummy; } ;
struct diff_filepair {TYPE_1__* two; } ;
struct collect_changed_submodules_cb_data {int /*<<< orphan*/  repo; struct object_id* commit_oid; struct string_list* changed; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 char* default_name_or_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct oid_array* submodule_commits (struct string_list*,char const*) ; 
 struct submodule* submodule_from_name (int /*<<< orphan*/ ,struct object_id const*,char const*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collect_changed_submodules_cb(struct diff_queue_struct *q,
					  struct diff_options *options,
					  void *data)
{
	struct collect_changed_submodules_cb_data *me = data;
	struct string_list *changed = me->changed;
	const struct object_id *commit_oid = me->commit_oid;
	int i;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		struct oid_array *commits;
		const struct submodule *submodule;
		const char *name;

		if (!S_ISGITLINK(p->two->mode))
			continue;

		submodule = submodule_from_path(me->repo,
						commit_oid, p->two->path);
		if (submodule)
			name = submodule->name;
		else {
			name = default_name_or_path(p->two->path);
			/* make sure name does not collide with existing one */
			if (name)
				submodule = submodule_from_name(me->repo,
								commit_oid, name);
			if (submodule) {
				warning("Submodule in commit %s at path: "
					"'%s' collides with a submodule named "
					"the same. Skipping it.",
					oid_to_hex(commit_oid), p->two->path);
				name = NULL;
			}
		}

		if (!name)
			continue;

		commits = submodule_commits(changed, name);
		oid_array_append(commits, &p->two->oid);
	}
}