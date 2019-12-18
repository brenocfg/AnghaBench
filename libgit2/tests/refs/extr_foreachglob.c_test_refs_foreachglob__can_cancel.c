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
 int git_reference_foreach_glob (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  interrupt_cb ; 
 int /*<<< orphan*/  repo ; 

void test_refs_foreachglob__can_cancel(void)
{
	int count = 0;

	cl_assert_equal_i(-1000, git_reference_foreach_glob(
		repo, "*", interrupt_cb, &count) );

	cl_assert_equal_i(11, count);
}