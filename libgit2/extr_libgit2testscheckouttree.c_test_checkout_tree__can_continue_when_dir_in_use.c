#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void test_checkout_tree__can_continue_when_dir_in_use(void)
{
#ifdef GIT_WIN32
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid oid;
	git_object *obj = NULL;

	opts.checkout_strategy = GIT_CHECKOUT_FORCE |
		GIT_CHECKOUT_SKIP_LOCKED_DIRECTORIES;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/dir"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));

	cl_assert(git_path_isfile("testrepo/a/b.txt"));

	git_object_free(obj);

	cl_git_pass(p_chdir("testrepo/a"));

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/master"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));

	cl_git_pass(p_chdir("../.."));

	cl_assert(git_path_is_empty_dir("testrepo/a"));

	git_object_free(obj);
#endif
}