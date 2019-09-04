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
struct pathspec {int dummy; } ;
struct object_array {unsigned int nr; TYPE_1__* objects; } ;
struct object {int /*<<< orphan*/  oid; } ;
struct grep_opt {scalar_t__ status_only; int /*<<< orphan*/  repo; } ;
struct TYPE_2__ {int /*<<< orphan*/  path; int /*<<< orphan*/  name; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 struct object* deref_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gitmodules_config_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ grep_object (struct grep_opt*,struct pathspec const*,struct object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ recurse_submodules ; 
 int /*<<< orphan*/  submodule_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int grep_objects(struct grep_opt *opt, const struct pathspec *pathspec,
			const struct object_array *list)
{
	unsigned int i;
	int hit = 0;
	const unsigned int nr = list->nr;

	for (i = 0; i < nr; i++) {
		struct object *real_obj;
		real_obj = deref_tag(opt->repo, list->objects[i].item,
				     NULL, 0);

		/* load the gitmodules file for this rev */
		if (recurse_submodules) {
			submodule_free(opt->repo);
			gitmodules_config_oid(&real_obj->oid);
		}
		if (grep_object(opt, pathspec, real_obj, list->objects[i].name,
				list->objects[i].path)) {
			hit = 1;
			if (opt->status_only)
				break;
		}
	}
	return hit;
}