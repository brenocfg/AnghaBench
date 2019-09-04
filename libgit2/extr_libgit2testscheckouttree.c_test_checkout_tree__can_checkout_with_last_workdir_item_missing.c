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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_checkout_tree__can_checkout_with_last_workdir_item_missing(void)
{
	git_index *index = NULL;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid tree_id, commit_id;
	git_tree *tree = NULL;
	git_commit *commit = NULL;

	git_repository_index(&index, g_repo);

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_reference_name_to_id(&commit_id, g_repo, "refs/heads/master"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &commit_id));

	cl_git_pass(git_checkout_tree(g_repo, (git_object *)commit, &opts));
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/master"));

	cl_git_pass(p_mkdir("./testrepo/this-is-dir", 0777));
	cl_git_mkfile("./testrepo/this-is-dir/contained_file", "content\n");

	cl_git_pass(git_index_add_bypath(index, "this-is-dir/contained_file"));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_index_write_tree(&tree_id, index));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));

	cl_git_pass(p_unlink("./testrepo/this-is-dir/contained_file"));

	opts.checkout_strategy = GIT_CHECKOUT_SAFE;

	opts.checkout_strategy = 1;
	git_checkout_tree(g_repo, (git_object *)tree, &opts);

	git_tree_free(tree);
	git_commit_free(commit);
	git_index_free(index);
}