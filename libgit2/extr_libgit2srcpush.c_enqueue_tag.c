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
typedef  int /*<<< orphan*/  git_tag ;
struct TYPE_3__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_push ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_TAG ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int git_packbuilder_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_tag_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enqueue_tag(git_object **out, git_push *push, git_oid *id)
{
	git_object *obj = NULL, *target = NULL;
	int error;

	if ((error = git_object_lookup(&obj, push->repo, id, GIT_OBJECT_TAG)) < 0)
		return error;

	while (git_object_type(obj) == GIT_OBJECT_TAG) {
		if ((error = git_packbuilder_insert(push->pb, git_object_id(obj), NULL)) < 0)
			break;

		if ((error = git_tag_target(&target, (git_tag *) obj)) < 0)
			break;

		git_object_free(obj);
		obj = target;
	}

	if (error < 0)
		git_object_free(obj);
	else
		*out = obj;

	return error;
}