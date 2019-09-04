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
struct TYPE_3__ {int bare; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,char*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 

void test_clone_nonetwork__bad_urls(void)
{
	/* Clone should clean up the mess if the URL isn't a git repository */
	cl_git_fail(git_clone(&g_repo, "not_a_repo", "./foo", &g_options));
	cl_assert(!git_path_exists("./foo"));
	g_options.bare = true;
	cl_git_fail(git_clone(&g_repo, "not_a_repo", "./foo", &g_options));
	cl_assert(!git_path_exists("./foo"));

	cl_git_fail(git_clone(&g_repo, "git://example.com:asdf", "./foo", &g_options));
	cl_git_fail(git_clone(&g_repo, "https://example.com:asdf/foo", "./foo", &g_options));
	cl_git_fail(git_clone(&g_repo, "git://github.com/git://github.com/foo/bar.git.git",
				"./foo", &g_options));
	cl_git_fail(git_clone(&g_repo, "arrbee:my/bad:password@github.com:1111/strange:words.git",
				"./foo", &g_options));
}