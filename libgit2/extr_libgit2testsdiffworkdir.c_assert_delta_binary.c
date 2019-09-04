#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int GIT_DIFF_FLAG_BINARY ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* git_patch_get_delta (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void assert_delta_binary(git_diff *diff, size_t idx, int is_binary)
{
	git_patch *patch;
	const git_diff_delta *delta;

	cl_git_pass(git_patch_from_diff(&patch, diff, idx));
	delta = git_patch_get_delta(patch);
	cl_assert_equal_b((delta->flags & GIT_DIFF_FLAG_BINARY), is_binary);
	git_patch_free(patch);
}