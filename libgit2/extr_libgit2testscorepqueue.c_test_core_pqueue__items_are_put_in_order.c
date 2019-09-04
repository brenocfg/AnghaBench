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

void test_core_pqueue__items_are_put_in_order(void)
{
	git_pqueue pq;
	int i, vals[20];

	cl_git_pass(git_pqueue_init(&pq, 0, 20, cmp_ints));

	for (i = 0; i < 20; ++i) {
		if (i < 10)
			vals[i] = 10 - i; /* 10 down to 1 */
		else
			vals[i] = i + 1;  /* 11 up to 20 */

		cl_git_pass(git_pqueue_insert(&pq, &vals[i]));
	}

	cl_assert_equal_i(20, git_pqueue_size(&pq));

	for (i = 1; i <= 20; ++i) {
		void *p = git_pqueue_pop(&pq);
		cl_assert(p);
		cl_assert_equal_i(i, *(int *)p);
	}

	cl_assert_equal_i(0, git_pqueue_size(&pq));

	git_pqueue_free(&pq);
}