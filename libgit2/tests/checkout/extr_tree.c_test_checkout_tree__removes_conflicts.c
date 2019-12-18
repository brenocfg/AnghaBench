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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_conflict (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_get_bypath (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_index_remove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_checkout_tree__removes_conflicts(void)
{
	git_oid commit_id;
	git_commit *commit;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_index *index;

	cl_git_pass(git_oid_fromstr(&commit_id, "afe4393b2b2a965f06acf2ca9658eaa01e0cd6b6"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &commit_id));

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_checkout_tree(g_repo, (const git_object *)commit, &opts));

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_remove(index, "executable.txt", 0));

	create_conflict("executable.txt");
	cl_git_mkfile("testrepo/executable.txt", "This is the conflict file.\n");

	create_conflict("other.txt");
	cl_git_mkfile("testrepo/other.txt", "This is another conflict file.\n");

	cl_git_pass(git_index_write(index));

	cl_git_pass(git_checkout_tree(g_repo, (const git_object *)commit, &opts));

	cl_assert_equal_p(NULL, git_index_get_bypath(index, "executable.txt", 1));
	cl_assert_equal_p(NULL, git_index_get_bypath(index, "executable.txt", 2));
	cl_assert_equal_p(NULL, git_index_get_bypath(index, "executable.txt", 3));

	cl_assert_equal_p(NULL, git_index_get_bypath(index, "other.txt", 1));
	cl_assert_equal_p(NULL, git_index_get_bypath(index, "other.txt", 2));
	cl_assert_equal_p(NULL, git_index_get_bypath(index, "other.txt", 3));

	cl_assert(!git_path_exists("testrepo/other.txt"));

	git_commit_free(commit);
	git_index_free(index);
}