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
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_to_buf (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__parsing_minimal_patch_succeeds(void)
{
	const char patch[] =
	    "diff --git a/obj1 b/obj2\n"
	    "index 1234567..7654321 10644\n"
	    "--- a/obj1\n"
	    "+++ b/obj2\n"
	    "@@ -1 +1 @@\n"
	    "-a\n"
	    "+\n";
	git_buf buf = GIT_BUF_INIT;
	git_diff *diff;

	cl_git_pass(git_diff_from_buffer(&diff, patch, strlen(patch)));
	cl_git_pass(git_diff_to_buf(&buf, diff, GIT_DIFF_FORMAT_PATCH));
	cl_assert_equal_s(patch, buf.ptr);

	git_diff_free(diff);
	git_buf_dispose(&buf);
}