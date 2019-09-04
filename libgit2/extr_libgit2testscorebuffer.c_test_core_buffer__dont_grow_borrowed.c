#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  asize; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_EINVALID ; 
 int /*<<< orphan*/  cl_assert_equal_i (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_attach_notowned (TYPE_1__*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  git_buf_grow (TYPE_1__*,int) ; 
 scalar_t__ strlen (char const*) ; 

void test_core_buffer__dont_grow_borrowed(void)
{
	const char *somestring = "blah blah";
	git_buf buf = GIT_BUF_INIT;

	git_buf_attach_notowned(&buf, somestring, strlen(somestring) + 1);
	cl_assert_equal_p(somestring, buf.ptr);
	cl_assert_equal_i(0, buf.asize);
	cl_assert_equal_i(strlen(somestring) + 1, buf.size);

	cl_git_fail_with(GIT_EINVALID, git_buf_grow(&buf, 1024));
}