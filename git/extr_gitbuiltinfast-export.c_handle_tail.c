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
struct string_list {int dummy; } ;
struct rev_info {int dummy; } ;
struct object_array {scalar_t__ nr; } ;
struct commit {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_object_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct object_array*) ; 
 int /*<<< orphan*/  handle_commit (struct commit*,struct rev_info*,struct string_list*) ; 
 scalar_t__ has_unshown_parent (struct commit*) ; 
 scalar_t__ object_array_pop (struct object_array*) ; 

__attribute__((used)) static void handle_tail(struct object_array *commits, struct rev_info *revs,
			struct string_list *paths_of_changed_objects)
{
	struct commit *commit;
	while (commits->nr) {
		commit = (struct commit *)object_array_pop(commits);
		if (has_unshown_parent(commit)) {
			/* Queue again, to be handled later */
			add_object_array(&commit->object, NULL, commits);
			return;
		}
		handle_commit(commit, revs, paths_of_changed_objects);
	}
}