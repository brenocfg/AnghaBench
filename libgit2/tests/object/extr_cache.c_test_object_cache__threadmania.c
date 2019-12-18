#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_thread ;
struct TYPE_2__ {int /*<<< orphan*/ * sha; } ;

/* Variables and functions */
 int REPEAT ; 
 int THREADCOUNT ; 
 void* cache_parsed (void*) ; 
 void* cache_raw (void*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_data ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git__free (void*) ; 
 void* git__malloc (int) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_thread_create (int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  git_thread_join (int /*<<< orphan*/ *,void**) ; 

void test_object_cache__threadmania(void)
{
	int try, th, max_i;
	void *data;
	void *(*fn)(void *);

#ifdef GIT_THREADS
	git_thread t[THREADCOUNT];
#endif

	for (max_i = 0; g_data[max_i].sha != NULL; ++max_i)
		/* count up */;

	for (try = 0; try < REPEAT; ++try) {

		cl_git_pass(git_repository_open(&g_repo, cl_fixture("testrepo.git")));

		for (th = 0; th < THREADCOUNT; ++th) {
			data = git__malloc(2 * sizeof(int));

			((int *)data)[0] = th;
			((int *)data)[1] = th % max_i;

			fn = (th & 1) ? cache_parsed : cache_raw;

#ifdef GIT_THREADS
			cl_git_pass(git_thread_create(&t[th], fn, data));
#else
			cl_assert(fn(data) == data);
			git__free(data);
#endif
		}

#ifdef GIT_THREADS
		for (th = 0; th < THREADCOUNT; ++th) {
			cl_git_pass(git_thread_join(&t[th], &data));
			cl_assert_equal_i(th, ((int *)data)[0]);
			git__free(data);
		}
#endif

		git_repository_free(g_repo);
		g_repo = NULL;
	}
}