#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct walk_object {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  walk_objects; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 struct walk_object* git_oidmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int git_oidmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct walk_object*) ; 
 int lookup_walk_object (struct walk_object**,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int retrieve_object(struct walk_object **out, git_packbuilder *pb, const git_oid *id)
{
	struct walk_object *obj;
	int error;

	if ((obj = git_oidmap_get(pb->walk_objects, id)) == NULL) {
		if ((error = lookup_walk_object(&obj, pb, id)) < 0)
			return error;

		if ((error = git_oidmap_set(pb->walk_objects, &obj->id, obj)) < 0)
			return error;
	}

	*out = obj;
	return 0;
}