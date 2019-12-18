#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char** strings; int count; } ;
struct TYPE_5__ {int checkout_strategy; TYPE_1__ paths; } ;

/* Variables and functions */
 int GIT_CHECKOUT_FORCE ; 
 int GIT_CHECKOUT_REMOVE_UNTRACKED ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_object ; 
 TYPE_2__ g_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_path_exists (char*) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_checkout_tree__can_checkout_with_pattern(void)
{
	char *entries[] = { "[l-z]*.txt" };

	/* reset to beginning of history (i.e. just a README file) */

	g_opts.checkout_strategy =
		GIT_CHECKOUT_FORCE | GIT_CHECKOUT_REMOVE_UNTRACKED;

	cl_git_pass(git_revparse_single(&g_object, g_repo, "8496071c1b46c854b31185ea97743be6a8774479"));

	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));
	cl_git_pass(
		git_repository_set_head_detached(g_repo, git_object_id(g_object)));

	git_object_free(g_object);
	g_object = NULL;

	cl_assert(git_path_exists("testrepo/README"));
	cl_assert(!git_path_exists("testrepo/branch_file.txt"));
	cl_assert(!git_path_exists("testrepo/link_to_new.txt"));
	cl_assert(!git_path_exists("testrepo/new.txt"));

	/* now to a narrow patterned checkout */

	g_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	g_opts.paths.strings = entries;
	g_opts.paths.count = 1;

	cl_git_pass(git_revparse_single(&g_object, g_repo, "refs/heads/master"));

	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));

	cl_assert(git_path_exists("testrepo/README"));
	cl_assert(!git_path_exists("testrepo/branch_file.txt"));
	cl_assert(git_path_exists("testrepo/link_to_new.txt"));
	cl_assert(git_path_exists("testrepo/new.txt"));
}