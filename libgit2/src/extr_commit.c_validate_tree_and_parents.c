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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/ * (* git_commit_parent_callback ) (size_t,void*) ;
struct TYPE_6__ {scalar_t__ size; } ;
typedef  TYPE_1__ git_array_oid_t ;

/* Variables and functions */
 int GIT_EMODIFIED ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_ERROR_OBJECT ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/ * git_array_alloc (TYPE_1__) ; 
 int /*<<< orphan*/  git_array_clear (TYPE_1__) ; 
 int /*<<< orphan*/  git_array_get (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object__is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int validate_tree_and_parents(git_array_oid_t *parents, git_repository *repo, const git_oid *tree,
	git_commit_parent_callback parent_cb, void *parent_payload,
	const git_oid *current_id, bool validate)
{
	size_t i;
	int error;
	git_oid *parent_cpy;
	const git_oid *parent;

	if (validate && !git_object__is_valid(repo, tree, GIT_OBJECT_TREE))
		return -1;

	i = 0;
	while ((parent = parent_cb(i, parent_payload)) != NULL) {
		if (validate && !git_object__is_valid(repo, parent, GIT_OBJECT_COMMIT)) {
			error = -1;
			goto on_error;
		}

		parent_cpy = git_array_alloc(*parents);
		GIT_ERROR_CHECK_ALLOC(parent_cpy);

		git_oid_cpy(parent_cpy, parent);
		i++;
	}

	if (current_id && (parents->size == 0 || git_oid_cmp(current_id, git_array_get(*parents, 0)))) {
		git_error_set(GIT_ERROR_OBJECT, "failed to create commit: current tip is not the first parent");
		error = GIT_EMODIFIED;
		goto on_error;
	}

	return 0;

on_error:
	git_array_clear(*parents);
	return error;
}