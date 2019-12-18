#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_string ; 
 int /*<<< orphan*/  test_string_x2 ; 

void test_core_buffer__0(void)
{
	git_buf buf = GIT_BUF_INIT;

	cl_assert(buf.size == 0);

	git_buf_puts(&buf, test_string);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(test_string, git_buf_cstr(&buf));

	git_buf_puts(&buf, test_string);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(test_string_x2, git_buf_cstr(&buf));

	git_buf_dispose(&buf);
}