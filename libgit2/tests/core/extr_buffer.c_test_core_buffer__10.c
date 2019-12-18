#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_join_n (TYPE_1__*,char,int,char*,...) ; 

void test_core_buffer__10(void)
{
	git_buf a = GIT_BUF_INIT;

	cl_git_pass(git_buf_join_n(&a, '/', 1, "test"));
	cl_assert_equal_s(a.ptr, "test");
	cl_git_pass(git_buf_join_n(&a, '/', 1, "string"));
	cl_assert_equal_s(a.ptr, "test/string");
	git_buf_clear(&a);
	cl_git_pass(git_buf_join_n(&a, '/', 3, "test", "string", "join"));
	cl_assert_equal_s(a.ptr, "test/string/join");
	cl_git_pass(git_buf_join_n(&a, '/', 2, a.ptr, "more"));
	cl_assert_equal_s(a.ptr, "test/string/join/test/string/join/more");

	git_buf_dispose(&a);
}