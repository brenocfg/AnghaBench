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
 int REPEAT ; 
 int THREADCOUNT ; 
 int* cache_quick (int*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_thread_create (int /*<<< orphan*/ *,int* (*) (int*),int*) ; 
 int /*<<< orphan*/  git_thread_join (int /*<<< orphan*/ *,void**) ; 

void test_object_cache__fast_thread_rush(void)
{
	int try, th, data[THREADCOUNT*2];
#ifdef GIT_THREADS
	git_thread t[THREADCOUNT*2];
#endif

	for (try = 0; try < REPEAT; ++try) {
		cl_git_pass(git_repository_open(&g_repo, cl_fixture("testrepo.git")));

		for (th = 0; th < THREADCOUNT*2; ++th) {
			data[th] = th;
#ifdef GIT_THREADS
			cl_git_pass(
				git_thread_create(&t[th], cache_quick, &data[th]));
#else
			cl_assert(cache_quick(&data[th]) == &data[th]);
#endif
		}

#ifdef GIT_THREADS
		for (th = 0; th < THREADCOUNT*2; ++th) {
			void *rval;
			cl_git_pass(git_thread_join(&t[th], &rval));
			cl_assert_equal_i(th, *((int *)rval));
		}
#endif

		git_repository_free(g_repo);
		g_repo = NULL;
	}
}