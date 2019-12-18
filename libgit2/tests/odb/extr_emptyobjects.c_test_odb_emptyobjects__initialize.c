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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_odb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_odb_emptyobjects__initialize(void)
{
	g_repo = cl_git_sandbox_init(TEST_REPO_PATH);
	cl_git_pass(git_repository_odb(&g_odb, g_repo));
}