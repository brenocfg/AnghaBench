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
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_AND_WORKDIR ; 
 int /*<<< orphan*/  assert_show (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  entry_count0 ; 
 int /*<<< orphan*/  entry_paths0 ; 
 int /*<<< orphan*/  entry_statuses0 ; 

void test_status_worktree__show_index_and_workdir(void)
{
	assert_show(entry_count0, entry_paths0, entry_statuses0,
		cl_git_sandbox_init("status"), GIT_STATUS_SHOW_INDEX_AND_WORKDIR, 0);
}