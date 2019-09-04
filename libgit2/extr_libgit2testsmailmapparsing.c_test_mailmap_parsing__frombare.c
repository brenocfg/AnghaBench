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
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_mailmap_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  check_mailmap_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cl_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  g_mailmap ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_mailmap_from_repository (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolved ; 
 int /*<<< orphan*/  resolved_bare ; 

void test_mailmap_parsing__frombare(void)
{
	g_repo = cl_git_sandbox_init("mailmap/.gitted");
	cl_git_pass(git_repository_set_bare(g_repo));
	cl_check(git_repository_is_bare(g_repo));

	cl_git_pass(git_mailmap_from_repository(&g_mailmap, g_repo));

	/* We should have parsed all of the entries, except for the untracked one */
	check_mailmap_entries(g_mailmap, entries, ARRAY_SIZE(entries) - 1);

	/* Check that resolving the entries works */
	check_mailmap_resolve(g_mailmap, resolved, ARRAY_SIZE(resolved));
	check_mailmap_resolve(
		g_mailmap, resolved_bare, ARRAY_SIZE(resolved_bare));
}