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
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  PATCH_ORIGINAL_TO_CHANGE_MIDDLE ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 

void test_patch_parse__lifetime_of_patch_does_not_depend_on_buffer(void)
{
	git_buf diff = GIT_BUF_INIT, rendered = GIT_BUF_INIT;
	git_patch *patch;

	cl_git_pass(git_buf_sets(&diff, PATCH_ORIGINAL_TO_CHANGE_MIDDLE));
	cl_git_pass(git_patch_from_buffer(&patch, diff.ptr, diff.size, NULL));
	git_buf_dispose(&diff);

	cl_git_pass(git_patch_to_buf(&rendered, patch));
	cl_assert_equal_s(PATCH_ORIGINAL_TO_CHANGE_MIDDLE, rendered.ptr);
	git_buf_dispose(&rendered);

	cl_git_pass(git_patch_to_buf(&rendered, patch));
	cl_assert_equal_s(PATCH_ORIGINAL_TO_CHANGE_MIDDLE, rendered.ptr);
	git_buf_dispose(&rendered);

	git_patch_free(patch);
}