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
 int /*<<< orphan*/  GIT_DIR_MODE ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,char*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_is_empty_dir (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int /*<<< orphan*/ ) ; 

void test_clone_nonetwork__do_not_clean_existing_directory(void)
{
	/* Clone should not remove the directory if it already exists, but
	 * Should clean up entries it creates. */
	p_mkdir("./foo", GIT_DIR_MODE);
	cl_git_fail(git_clone(&g_repo, "not_a_repo", "./foo", &g_options));
	cl_assert(git_path_is_empty_dir("./foo"));

	/* Try again with a bare repository. */
	g_options.bare = true;
	cl_git_fail(git_clone(&g_repo, "not_a_repo", "./foo", &g_options));
	cl_assert(git_path_is_empty_dir("./foo"));
}