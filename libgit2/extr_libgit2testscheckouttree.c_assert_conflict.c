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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_3__ {int /*<<< orphan*/  checkout_strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_ECONFLICT ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_object ; 
 TYPE_1__ g_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_branch_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 

void assert_conflict(
	const char *entry_path,
	const char *new_content,
	const char *parent_sha,
	const char *commit_sha)
{
	git_index *index;
	git_object *hack_tree;
	git_reference *branch, *head;
	git_buf file_path = GIT_BUF_INIT;

	cl_git_pass(git_repository_index(&index, g_repo));

	/* Create a branch pointing at the parent */
	cl_git_pass(git_revparse_single(&g_object, g_repo, parent_sha));
	cl_git_pass(git_branch_create(&branch, g_repo,
		"potential_conflict", (git_commit *)g_object, 0));

	/* Make HEAD point to this branch */
	cl_git_pass(git_reference_symbolic_create(
		&head, g_repo, "HEAD", git_reference_name(branch), 1, NULL));
	git_reference_free(head);
	git_reference_free(branch);

	/* Checkout the parent */
	g_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));

	/* Hack-ishy workaound to ensure *all* the index entries
	 * match the content of the tree
	 */
	cl_git_pass(git_object_peel(&hack_tree, g_object, GIT_OBJECT_TREE));
	cl_git_pass(git_index_read_tree(index, (git_tree *)hack_tree));
	cl_git_pass(git_index_write(index));
	git_object_free(hack_tree);
	git_object_free(g_object);
	g_object = NULL;

	/* Create a conflicting file */
	cl_git_pass(git_buf_joinpath(&file_path, "./testrepo", entry_path));
	cl_git_mkfile(git_buf_cstr(&file_path), new_content);
	git_buf_dispose(&file_path);

	/* Trying to checkout the original commit */
	cl_git_pass(git_revparse_single(&g_object, g_repo, commit_sha));

	g_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	cl_assert_equal_i(
		GIT_ECONFLICT, git_checkout_tree(g_repo, g_object, &g_opts));

	/* Stage the conflicting change */
	cl_git_pass(git_index_add_bypath(index, entry_path));
	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_assert_equal_i(
		GIT_ECONFLICT, git_checkout_tree(g_repo, g_object, &g_opts));
}