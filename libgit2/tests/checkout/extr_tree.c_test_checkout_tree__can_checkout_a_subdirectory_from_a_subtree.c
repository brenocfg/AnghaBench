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
struct TYPE_5__ {TYPE_1__ paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object ; 
 TYPE_2__ g_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void test_checkout_tree__can_checkout_a_subdirectory_from_a_subtree(void)
{
	char *entries[] = { "de/" };

	g_opts.paths.strings = entries;
	g_opts.paths.count = 1;

	cl_git_pass(git_revparse_single(&g_object, g_repo, "subtrees:ab"));

	cl_assert_equal_i(false, git_path_isdir("./testrepo/de/"));

	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));

	cl_assert_equal_i(true, git_path_isfile("./testrepo/de/2.txt"));
	cl_assert_equal_i(true, git_path_isfile("./testrepo/de/fgh/1.txt"));
}