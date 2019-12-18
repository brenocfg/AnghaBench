#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  progress_cb; } ;
typedef  TYPE_1__ git_stash_apply_options ;

/* Variables and functions */
 TYPE_1__ GIT_STASH_APPLY_OPTIONS_INIT ; 
 int /*<<< orphan*/  aborting_progress_cb ; 
 int /*<<< orphan*/  cl_git_fail_with (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  repo ; 

void test_stash_apply__progress_cb_can_abort(void)
{
	git_stash_apply_options opts = GIT_STASH_APPLY_OPTIONS_INIT;

	opts.progress_cb = aborting_progress_cb;

	cl_git_fail_with(-44, git_stash_apply(repo, 0, &opts));
}