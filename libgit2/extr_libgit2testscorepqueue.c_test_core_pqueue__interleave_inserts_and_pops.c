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
typedef  int /*<<< orphan*/  git_pqueue ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (void*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_ints ; 
 int /*<<< orphan*/  git_pqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pqueue_insert (int /*<<< orphan*/ *,int*) ; 
 void* git_pqueue_pop (int /*<<< orphan*/ *) ; 
 int git_pqueue_size (int /*<<< orphan*/ *) ; 

void test_core_pqueue__interleave_inserts_and_pops(void)
{
	git_pqueue pq;
	int chunk, v, i, vals[200];

	cl_git_pass(git_pqueue_init(&pq, 0, 20, cmp_ints));

	for (v = 0, chunk = 20; chunk <= 200; chunk += 20) {
		/* push the next 20 */
		for (; v < chunk; ++v) {
			vals[v] = (v & 1) ? 200 - v : v;
			cl_git_pass(git_pqueue_insert(&pq, &vals[v]));
		}

		/* pop the lowest 10 */
		for (i = 0; i < 10; ++i)
			(void)git_pqueue_pop(&pq);
	}

	cl_assert_equal_i(100, git_pqueue_size(&pq));

	/* at this point, we've popped 0-99 */

	for (v = 100; v < 200; ++v) {
		void *p = git_pqueue_pop(&pq);
		cl_assert(p);
		cl_assert_equal_i(v, *(int *)p);
	}

	cl_assert_equal_i(0, git_pqueue_size(&pq));

	git_pqueue_free(&pq);
}