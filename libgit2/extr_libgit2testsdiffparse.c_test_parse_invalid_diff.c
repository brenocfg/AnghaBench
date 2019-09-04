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
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR ; 
 char const* PATCH_BINARY_DELTA ; 
 char const* PATCH_BINARY_LITERAL ; 
 char const* PATCH_ORIGINAL_TO_CHANGE_FIRSTLINE ; 
 char const* PATCH_ORIGINAL_TO_CHANGE_MIDDLE ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_parse_invalid_diff(const char *invalid_diff)
{
	git_diff *diff;
	git_buf buf = GIT_BUF_INIT;

	/* throw some random (legitimate) diffs in with the given invalid
	 * one.
	 */
	git_buf_puts(&buf, PATCH_ORIGINAL_TO_CHANGE_FIRSTLINE);
	git_buf_puts(&buf, PATCH_BINARY_DELTA);
	git_buf_puts(&buf, invalid_diff);
	git_buf_puts(&buf, PATCH_ORIGINAL_TO_CHANGE_MIDDLE);
	git_buf_puts(&buf, PATCH_BINARY_LITERAL);

	cl_git_fail_with(GIT_ERROR,
		git_diff_from_buffer(&diff, buf.ptr, buf.size));

	git_buf_dispose(&buf);
}