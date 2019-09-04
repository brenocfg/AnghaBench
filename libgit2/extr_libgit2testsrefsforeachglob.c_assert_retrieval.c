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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_cb ; 
 int /*<<< orphan*/  git_reference_foreach_glob (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void assert_retrieval(const char *glob, int expected_count)
{
	int count = 0;

	cl_git_pass(git_reference_foreach_glob(repo, glob, count_cb, &count));

	cl_assert_equal_i(expected_count, count);
}