#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  oid_old; } ;
typedef  TYPE_1__ git_reflog_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEX_ZERO ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int entrycount ; 
 int /*<<< orphan*/  g_reflog ; 
 scalar_t__ git_oid_streq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_drop (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* git_reflog_entry_byindex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ ) ; 

void test_refs_reflog_drop__can_drop_the_oldest_entry_and_rewrite_the_log_history(void)
{
	const git_reflog_entry *entry;

	cl_assert(entrycount > 2);

	cl_git_pass(git_reflog_drop(g_reflog, entrycount - 1, 1));
	cl_assert_equal_sz(entrycount - 1, git_reflog_entrycount(g_reflog));

	entry = git_reflog_entry_byindex(g_reflog, entrycount - 2);
	cl_assert(git_oid_streq(&entry->oid_old, GIT_OID_HEX_ZERO) == 0);
}