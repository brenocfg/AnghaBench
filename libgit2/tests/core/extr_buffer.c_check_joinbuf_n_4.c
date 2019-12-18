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
 int /*<<< orphan*/  git_buf_join_n (int /*<<< orphan*/ *,char,int,char const*,char const*,char const*,char const*) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_joinbuf_n_4(
	const char *a,
	const char *b,
	const char *c,
	const char *d,
	const char *expected)
{
	char sep = ';';
	git_buf buf = GIT_BUF_INIT;
	git_buf_join_n(&buf, sep, 4, a, b, c, d);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(expected, git_buf_cstr(&buf));
	git_buf_dispose(&buf);
}