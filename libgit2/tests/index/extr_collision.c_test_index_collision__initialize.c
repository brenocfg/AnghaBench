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
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_empty_id ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_odb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_index_collision__initialize(void)
{
	g_repo = cl_git_sandbox_init("empty_standard_repo");
	cl_git_pass(git_repository_odb(&g_odb, g_repo));
	cl_git_pass(git_repository_index(&g_index, g_repo));

	cl_git_pass(git_odb_write(&g_empty_id, g_odb, "", 0, GIT_OBJECT_BLOB));
}