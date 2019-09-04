#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tag ;
struct TYPE_6__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
#define  GIT_OBJECT_BLOB 131 
#define  GIT_OBJECT_COMMIT 130 
#define  GIT_OBJECT_TAG 129 
#define  GIT_OBJECT_TREE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_object_type (int /*<<< orphan*/ *) ; 
 int git_packbuilder_insert (TYPE_1__*,int /*<<< orphan*/  const*,char const*) ; 
 int git_packbuilder_insert_commit (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int git_packbuilder_insert_tree (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_tag_target_id (int /*<<< orphan*/ *) ; 

int git_packbuilder_insert_recur(git_packbuilder *pb, const git_oid *id, const char *name)
{
	git_object *obj;
	int error;

	assert(pb && id);

	if ((error = git_object_lookup(&obj, pb->repo, id, GIT_OBJECT_ANY)) < 0)
		return error;

	switch (git_object_type(obj)) {
	case GIT_OBJECT_BLOB:
		error = git_packbuilder_insert(pb, id, name);
		break;
	case GIT_OBJECT_TREE:
		error = git_packbuilder_insert_tree(pb, id);
		break;
	case GIT_OBJECT_COMMIT:
		error = git_packbuilder_insert_commit(pb, id);
		break;
	case GIT_OBJECT_TAG:
		if ((error = git_packbuilder_insert(pb, id, name)) < 0)
			goto cleanup;
		error = git_packbuilder_insert_recur(pb, git_tag_target_id((git_tag *) obj), NULL);
		break;

	default:
		git_error_set(GIT_ERROR_INVALID, "unknown object type");
		error = -1;
	}

cleanup:
	git_object_free(obj);
	return error;
}