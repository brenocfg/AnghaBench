#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
struct TYPE_7__ {TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 char* PATCH_CRLF ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* git_patch_get_delta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__crlf(void)
{
	const char *text = PATCH_CRLF;
	git_diff *diff;
	git_patch *patch;
	const git_diff_delta *delta;

	cl_git_pass(git_diff_from_buffer(&diff, text, strlen(text)));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	delta = git_patch_get_delta(patch);

	cl_assert_equal_s(delta->old_file.path, "test-file");
	cl_assert_equal_s(delta->new_file.path, "test-file");

	git_patch_free(patch);
	git_diff_free(diff);
}