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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_5__ {int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_SAFE ; 
 int GIT_CHECKOUT_UPDATE_ONLY ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_file_contents_nocr (char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 

void test_checkout_tree__can_update_only(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid oid;
	git_object *obj = NULL;

	/* first let's get things into a known state - by checkout out the HEAD */

	assert_on_branch(g_repo, "master");

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	cl_git_pass(git_checkout_head(g_repo, &opts));

	cl_assert(!git_path_isdir("testrepo/a"));

	check_file_contents_nocr("testrepo/branch_file.txt", "hi\nbye!\n");

	/* now checkout branch but with update only */

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_UPDATE_ONLY;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/dir"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/dir"));

	assert_on_branch(g_repo, "dir");

	/* this normally would have been created (which was tested separately in
	 * the test_checkout_tree__can_switch_branches test), but with
	 * UPDATE_ONLY it will not have been created.
	 */
	cl_assert(!git_path_isdir("testrepo/a"));

	/* but this file still should have been updated */
	check_file_contents_nocr("testrepo/branch_file.txt", "hi\n");

	git_object_free(obj);
}