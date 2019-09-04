#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_REPO ; 
 int /*<<< orphan*/  WORKTREE_REPO ; 
 int /*<<< orphan*/  assert_worktree_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fixture ; 

void test_worktree_open__repository(void)
{
	assert_worktree_valid(fixture.worktree, COMMON_REPO, WORKTREE_REPO);
}