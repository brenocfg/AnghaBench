#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  new_prefix; int /*<<< orphan*/  old_prefix; } ;
struct TYPE_12__ {TYPE_4__* delta; TYPE_2__ diff_opts; } ;
typedef  TYPE_5__ git_patch ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_11__ {TYPE_3__ new_file; TYPE_1__ old_file; } ;

/* Variables and functions */
 char* PATCH_ORIGINAL_NEW_FILE_WITH_SPACE ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (TYPE_5__*) ; 
 int /*<<< orphan*/  git_patch_from_diff (TYPE_5__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__new_file_with_space(void)
{
	const char *content = PATCH_ORIGINAL_NEW_FILE_WITH_SPACE;
	git_patch *patch;
	git_diff *diff;

	cl_git_pass(git_diff_from_buffer(&diff, content, strlen(content)));
	cl_git_pass(git_patch_from_diff((git_patch **) &patch, diff, 0));

	cl_assert_equal_p(patch->diff_opts.old_prefix, NULL);
	cl_assert_equal_p(patch->delta->old_file.path, NULL);
	cl_assert_equal_s(patch->diff_opts.new_prefix, "b/");
	cl_assert_equal_s(patch->delta->new_file.path, "sp ace.txt");

	git_patch_free(patch);
	git_diff_free(diff);
}