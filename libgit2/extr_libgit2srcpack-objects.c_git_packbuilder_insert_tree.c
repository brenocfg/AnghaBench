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
struct tree_walk_context {int /*<<< orphan*/  buf; int /*<<< orphan*/  member_1; TYPE_1__* member_0; } ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_4__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_TREEWALK_PRE ; 
 int /*<<< orphan*/  cb_tree_walk ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_packbuilder_insert (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int git_tree_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tree_walk_context*) ; 

int git_packbuilder_insert_tree(git_packbuilder *pb, const git_oid *oid)
{
	int error;
	git_tree *tree = NULL;
	struct tree_walk_context context = { pb, GIT_BUF_INIT };

	if (!(error = git_tree_lookup(&tree, pb->repo, oid)) &&
	    !(error = git_packbuilder_insert(pb, oid, NULL)))
		error = git_tree_walk(tree, GIT_TREEWALK_PRE, cb_tree_walk, &context);

	git_tree_free(tree);
	git_buf_dispose(&context.buf);
	return error;
}