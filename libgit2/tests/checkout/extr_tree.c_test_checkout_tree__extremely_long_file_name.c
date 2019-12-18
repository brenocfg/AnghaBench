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
struct TYPE_3__ {int /*<<< orphan*/  checkout_strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object ; 
 TYPE_1__ g_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int git_path_exists (char*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

void test_checkout_tree__extremely_long_file_name(void)
{
	/* A utf-8 string with 83 characters, but 249 bytes. */
	const char *longname = "\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97\xe5\x8f\x97";
	char path[1024];

	g_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	cl_git_pass(git_revparse_single(&g_object, g_repo, "long-file-name"));
	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));

	sprintf(path, "testrepo/%s.txt", longname);
	cl_assert(git_path_exists(path));

	git_object_free(g_object);
	cl_git_pass(git_revparse_single(&g_object, g_repo, "master"));
	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));
	cl_assert(!git_path_exists(path));
}