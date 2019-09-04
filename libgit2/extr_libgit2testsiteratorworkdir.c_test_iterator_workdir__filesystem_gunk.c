#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_futils_mkdir (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_iterator_for_filesystem (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_iterator_workdir__filesystem_gunk(void)
{
	git_iterator *i;
	git_buf parent = GIT_BUF_INIT;
	int n;

	if (!cl_is_env_set("GITTEST_INVASIVE_SPEED"))
		cl_skip();

	g_repo = cl_git_sandbox_init("testrepo");

	for (n = 0; n < 100000; n++) {
		git_buf_clear(&parent);
		git_buf_printf(&parent, "%s/refs/heads/foo/%d/subdir",
			git_repository_path(g_repo), n);
		cl_assert(!git_buf_oom(&parent));

		cl_git_pass(git_futils_mkdir(parent.ptr, 0775, GIT_MKDIR_PATH));
	}

	cl_git_pass(git_iterator_for_filesystem(&i, "testrepo/.git/refs", NULL));

	/* should only have 16 items, since we're not asking for trees to be
	 * returned.  the goal of this test is simply to not crash.
	 */
	expect_iterator_items(i, 16, NULL, 15, NULL);
	git_iterator_free(i);
	git_buf_dispose(&parent);
}