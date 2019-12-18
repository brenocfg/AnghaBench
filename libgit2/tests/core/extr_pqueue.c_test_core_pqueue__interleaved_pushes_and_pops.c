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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_ints_like_commit_time ; 
 int /*<<< orphan*/  git_pqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pqueue_insert (int /*<<< orphan*/ *,int*) ; 
 int* git_pqueue_pop (int /*<<< orphan*/ *) ; 
 int git_pqueue_size (int /*<<< orphan*/ *) ; 

void test_core_pqueue__interleaved_pushes_and_pops(void)
{
	git_pqueue pq;
	int i, j, *val;
	static int commands[] =
		{ 6, 9, 8, 0, 5, 0, 7, 0, 4, 3, 0, 0, 0, 4, 0, 2, 0, 1, 0, 0, -1 };
	static int expected[] =
		{ 9, 8, 7, 6, 5, 4, 4, 3, 2, 1, -1 };

	cl_git_pass(git_pqueue_init(&pq, 0, 10, cmp_ints_like_commit_time));

	for (i = 0, j = 0; commands[i] >= 0; ++i) {
		if (!commands[i]) {
			cl_assert((val = git_pqueue_pop(&pq)) != NULL);
			cl_assert_equal_i(expected[j], *val);
			++j;
		} else {
			cl_git_pass(git_pqueue_insert(&pq, &commands[i]));
		}
	}

	cl_assert_equal_i(0, git_pqueue_size(&pq));
	git_pqueue_free(&pq);
}