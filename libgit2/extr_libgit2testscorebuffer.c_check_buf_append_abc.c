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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
check_buf_append_abc(
	const char* buf_a,
	const char* buf_b,
	const char* buf_c,
	const char* expected_ab,
	const char* expected_abc,
	const char* expected_abca,
	const char* expected_abcab,
	const char* expected_abcabc)
{
	git_buf buf = GIT_BUF_INIT;

	git_buf_sets(&buf, buf_a);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(buf_a, git_buf_cstr(&buf));

	git_buf_puts(&buf, buf_b);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(expected_ab, git_buf_cstr(&buf));

	git_buf_puts(&buf, buf_c);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(expected_abc, git_buf_cstr(&buf));

	git_buf_puts(&buf, buf_a);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(expected_abca, git_buf_cstr(&buf));

	git_buf_puts(&buf, buf_b);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(expected_abcab, git_buf_cstr(&buf));

	git_buf_puts(&buf, buf_c);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(expected_abcabc, git_buf_cstr(&buf));

	git_buf_dispose(&buf);
}