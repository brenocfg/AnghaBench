#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  message; int /*<<< orphan*/  klass; } ;

/* Variables and functions */
 int GIT_ADD_SIZET_OVERFLOW (size_t*,int,int) ; 
 int /*<<< orphan*/  GIT_ERROR_NOMEMORY ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_error_last () ; 

void test_core_errors__integer_overflow_sets_oom(void)
{
	size_t out;

	git_error_clear();
	cl_assert(!GIT_ADD_SIZET_OVERFLOW(&out, SIZE_MAX-1, 1));
	cl_assert_equal_p(NULL, git_error_last());

	git_error_clear();
	cl_assert(!GIT_ADD_SIZET_OVERFLOW(&out, 42, 69));
	cl_assert_equal_p(NULL, git_error_last());

	git_error_clear();
	cl_assert(GIT_ADD_SIZET_OVERFLOW(&out, SIZE_MAX, SIZE_MAX));
	cl_assert_equal_i(GIT_ERROR_NOMEMORY, git_error_last()->klass);
	cl_assert_equal_s("Out of memory", git_error_last()->message);

	git_error_clear();
	cl_assert(GIT_ADD_SIZET_OVERFLOW(&out, SIZE_MAX, SIZE_MAX));
	cl_assert_equal_i(GIT_ERROR_NOMEMORY, git_error_last()->klass);
	cl_assert_equal_s("Out of memory", git_error_last()->message);
}