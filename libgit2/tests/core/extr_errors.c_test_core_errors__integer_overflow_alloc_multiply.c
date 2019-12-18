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
struct TYPE_2__ {int /*<<< orphan*/  message; int /*<<< orphan*/  klass; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_NOMEMORY ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  test_arraysize_multiply (int,int) ; 

void test_core_errors__integer_overflow_alloc_multiply(void)
{
	cl_git_pass(test_arraysize_multiply(10, 10));
	cl_git_pass(test_arraysize_multiply(1000, 1000));
	cl_git_pass(test_arraysize_multiply(SIZE_MAX/sizeof(void *), sizeof(void *)));
	cl_git_pass(test_arraysize_multiply(0, 10));
	cl_git_pass(test_arraysize_multiply(10, 0));

	cl_git_fail(test_arraysize_multiply(SIZE_MAX-1, sizeof(void *)));
	cl_git_fail(test_arraysize_multiply((SIZE_MAX/sizeof(void *))+1, sizeof(void *)));

	cl_assert_equal_i(GIT_ERROR_NOMEMORY, git_error_last()->klass);
	cl_assert_equal_s("Out of memory", git_error_last()->message);
}