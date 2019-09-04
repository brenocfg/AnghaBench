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
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_quote (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void expect_quote_pass(const char *expected, const char *str)
{
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_puts(&buf, str));
	cl_git_pass(git_buf_quote(&buf));

	cl_assert_equal_s(expected, git_buf_cstr(&buf));
	cl_assert_equal_i(strlen(expected), git_buf_len(&buf));

	git_buf_dispose(&buf);
}