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
 int /*<<< orphan*/  fixture ; 
 int /*<<< orphan*/  setup_fixture_worktree (int /*<<< orphan*/ *) ; 

void test_worktree_reflog__initialize(void)
{
	setup_fixture_worktree(&fixture);
}