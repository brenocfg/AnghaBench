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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int entrycount ; 
 int /*<<< orphan*/  g_reflog ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reflog_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reflog_write (int /*<<< orphan*/ ) ; 

void test_refs_reflog_drop__can_persist_deletion_on_disk(void)
{
	cl_assert(entrycount > 2);

	cl_git_pass(git_reflog_drop(g_reflog, 0, 1));
	cl_assert_equal_sz(entrycount - 1, git_reflog_entrycount(g_reflog));
	cl_git_pass(git_reflog_write(g_reflog));

	git_reflog_free(g_reflog);

	git_reflog_read(&g_reflog, g_repo, "HEAD");

	cl_assert_equal_sz(entrycount - 1, git_reflog_entrycount(g_reflog));
}