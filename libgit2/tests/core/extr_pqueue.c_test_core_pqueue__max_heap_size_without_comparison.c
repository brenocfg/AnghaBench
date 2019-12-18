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
 int /*<<< orphan*/  GIT_PQUEUE_FIXED_SIZE ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pqueue_insert (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  git_pqueue_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pqueue_size (int /*<<< orphan*/ *) ; 

void test_core_pqueue__max_heap_size_without_comparison(void)
{
	git_pqueue pq;
	int i, vals[100] = { 0 };

	cl_git_pass(git_pqueue_init(&pq, GIT_PQUEUE_FIXED_SIZE, 50, NULL));

	for (i = 0; i < 100; ++i)
		cl_git_pass(git_pqueue_insert(&pq, &vals[i]));

	cl_assert_equal_i(50, git_pqueue_size(&pq));

	/* As we have no comparison function, we cannot make any
	 * actual assumptions about which entries are part of the
	 * pqueue */
	for (i = 0; i < 50; ++i)
		cl_assert(git_pqueue_pop(&pq));

	cl_assert_equal_i(0, git_pqueue_size(&pq));

	git_pqueue_free(&pq);
}