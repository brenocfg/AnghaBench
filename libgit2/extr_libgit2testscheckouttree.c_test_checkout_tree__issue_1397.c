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
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  check_file_contents (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  test_checkout_tree__cleanup () ; 

void test_checkout_tree__issue_1397(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	const char *partial_oid = "8a7ef04";
	git_object *tree = NULL;

	test_checkout_tree__cleanup(); /* cleanup default checkout */

	g_repo = cl_git_sandbox_init("issue_1397");

	cl_repo_set_bool(g_repo, "core.autocrlf", true);

	cl_git_pass(git_revparse_single(&tree, g_repo, partial_oid));

	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_checkout_tree(g_repo, tree, &opts));

	check_file_contents("./issue_1397/crlf_file.txt", "first line\r\nsecond line\r\nboth with crlf");

	git_object_free(tree);
}