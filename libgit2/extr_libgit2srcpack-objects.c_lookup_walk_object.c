#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct walk_object {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  object_pool; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  git_error_set_oom () ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct walk_object* git_pool_mallocz (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lookup_walk_object(struct walk_object **out, git_packbuilder *pb, const git_oid *id)
{
	struct walk_object *obj;

	obj = git_pool_mallocz(&pb->object_pool, 1);
	if (!obj) {
		git_error_set_oom();
		return -1;
	}

	git_oid_cpy(&obj->id, id);

	*out = obj;
	return 0;
}