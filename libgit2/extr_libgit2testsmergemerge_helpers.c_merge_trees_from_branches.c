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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_merge_options ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_merge_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_merge_trees (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

int merge_trees_from_branches(
	git_index **index, git_repository *repo,
	const char *ours_name, const char *theirs_name,
	git_merge_options *opts)
{
	git_commit *our_commit, *their_commit, *ancestor_commit = NULL;
	git_tree *our_tree, *their_tree, *ancestor_tree = NULL;
	git_oid our_oid, their_oid, ancestor_oid;
	git_buf branch_buf = GIT_BUF_INIT;
	int error;

	git_buf_printf(&branch_buf, "%s%s", GIT_REFS_HEADS_DIR, ours_name);
	cl_git_pass(git_reference_name_to_id(&our_oid, repo, branch_buf.ptr));
	cl_git_pass(git_commit_lookup(&our_commit, repo, &our_oid));

	git_buf_clear(&branch_buf);
	git_buf_printf(&branch_buf, "%s%s", GIT_REFS_HEADS_DIR, theirs_name);
	cl_git_pass(git_reference_name_to_id(&their_oid, repo, branch_buf.ptr));
	cl_git_pass(git_commit_lookup(&their_commit, repo, &their_oid));

	error = git_merge_base(&ancestor_oid, repo, git_commit_id(our_commit), git_commit_id(their_commit));

	if (error != GIT_ENOTFOUND) {
		cl_git_pass(error);

		cl_git_pass(git_commit_lookup(&ancestor_commit, repo, &ancestor_oid));
		cl_git_pass(git_commit_tree(&ancestor_tree, ancestor_commit));
	}

	cl_git_pass(git_commit_tree(&our_tree, our_commit));
	cl_git_pass(git_commit_tree(&their_tree, their_commit));

	error = git_merge_trees(index, repo, ancestor_tree, our_tree, their_tree, opts);

	git_buf_dispose(&branch_buf);
	git_tree_free(our_tree);
	git_tree_free(their_tree);
	git_tree_free(ancestor_tree);
	git_commit_free(our_commit);
	git_commit_free(their_commit);
	git_commit_free(ancestor_commit);

	return error;
}