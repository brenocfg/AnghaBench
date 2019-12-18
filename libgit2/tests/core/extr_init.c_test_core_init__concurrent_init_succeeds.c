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
typedef  int /*<<< orphan*/  git_thread ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_sandbox_set_search_path_defaults () ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_libgit2_init () ; 
 int /*<<< orphan*/  git_libgit2_shutdown () ; 
 int /*<<< orphan*/  git_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_thread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit ; 

void test_core_init__concurrent_init_succeeds(void)
{
#ifdef GIT_THREADS
	git_thread threads[10];
	unsigned i;

	cl_assert_equal_i(2, git_libgit2_init());

	for (i = 0; i < ARRAY_SIZE(threads); i++)
		git_thread_create(&threads[i], reinit, NULL);
	for (i = 0; i < ARRAY_SIZE(threads); i++)
		git_thread_join(&threads[i], NULL);

	cl_assert_equal_i(1, git_libgit2_shutdown());
	cl_sandbox_set_search_path_defaults();
#else
	cl_skip();
#endif
}