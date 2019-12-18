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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_path_make_relative (TYPE_1__*,char const*) ; 

__attribute__((used)) static void test_make_relative(
	const char *expected_path,
	const char *path,
	const char *parent,
	int expected_status)
{
	git_buf buf = GIT_BUF_INIT;
	git_buf_puts(&buf, path);
	cl_assert_equal_i(expected_status, git_path_make_relative(&buf, parent));
	cl_assert_equal_s(expected_path, buf.ptr);
	git_buf_dispose(&buf);
}