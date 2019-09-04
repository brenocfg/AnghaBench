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
typedef  int /*<<< orphan*/  git_status_list ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_nsecs () ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_nsec__status_doesnt_clear_nsecs(void)
{
	git_status_list *statuslist;

	cl_git_pass(git_status_list_new(&statuslist, repo, NULL));

	git_index_read(repo_index, 1);
	cl_assert_equal_b(true, has_nsecs());

	git_status_list_free(statuslist);
}