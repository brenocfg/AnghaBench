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
struct merge_diff_find_data {int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  git_merge_diff_list ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int git_iterator_walk (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,struct merge_diff_find_data*) ; 
 int /*<<< orphan*/  queue_difference ; 

int git_merge_diff_list__find_differences(
	git_merge_diff_list *diff_list,
	git_iterator *ancestor_iter,
	git_iterator *our_iter,
	git_iterator *their_iter)
{
	git_iterator *iterators[3] = { ancestor_iter, our_iter, their_iter };
	struct merge_diff_find_data find_data = { diff_list };

	return git_iterator_walk(iterators, 3, queue_difference, &find_data);
}