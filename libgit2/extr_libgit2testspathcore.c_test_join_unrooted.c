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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_join_unrooted (TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_join_unrooted(
	const char *expected_result,
	ssize_t expected_rootlen,
	const char *path,
	const char *base)
{
	git_buf result = GIT_BUF_INIT;
	ssize_t root_at;

	cl_git_pass(git_path_join_unrooted(&result, path, base, &root_at));
	cl_assert_equal_s(expected_result, result.ptr);
	cl_assert_equal_i(expected_rootlen, root_at);

	git_buf_dispose(&result);
}