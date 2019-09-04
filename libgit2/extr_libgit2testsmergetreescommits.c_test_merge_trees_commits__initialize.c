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
 int /*<<< orphan*/  TEST_REPO_PATH ; 
 int /*<<< orphan*/  cl_git_sandbox_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_trees_commits__initialize(void)
{
	repo = cl_git_sandbox_init(TEST_REPO_PATH);
}