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

/* Variables and functions */
 int /*<<< orphan*/  GIT_STATUS_SHOW_WORKDIR_ONLY ; 
 int /*<<< orphan*/  assert_show (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  entry_count6 ; 
 int /*<<< orphan*/  entry_paths6 ; 
 int /*<<< orphan*/  entry_statuses6 ; 

void test_status_worktree__show_workdir_only(void)
{
	assert_show(entry_count6, entry_paths6, entry_statuses6,
		cl_git_sandbox_init("status"), GIT_STATUS_SHOW_WORKDIR_ONLY, 0);
}