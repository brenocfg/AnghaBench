#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct walk_object {int seen; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_5__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree_id (int /*<<< orphan*/ *) ; 
 int git_packbuilder_insert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int insert_tree (TYPE_1__*,int /*<<< orphan*/ *) ; 

int insert_commit(git_packbuilder *pb, struct walk_object *obj)
{
	int error;
	git_commit *commit = NULL;
	git_tree *tree = NULL;

	obj->seen = 1;

	if ((error = git_packbuilder_insert(pb, &obj->id, NULL)) < 0)
		return error;

	if ((error = git_commit_lookup(&commit, pb->repo, &obj->id)) < 0)
		return error;

	if ((error = git_tree_lookup(&tree, pb->repo, git_commit_tree_id(commit))) < 0)
		goto cleanup;

	if ((error = insert_tree(pb, tree)) < 0)
		goto cleanup;

cleanup:
	git_commit_free(commit);
	git_tree_free(tree);
	return error;
}