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
struct TYPE_3__ {int /*<<< orphan*/  oid_cur; int /*<<< orphan*/  oid_old; } ;
typedef  TYPE_1__ git_reflog_entry ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int entrycount ; 
 int /*<<< orphan*/  g_reflog ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_drop (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* git_reflog_entry_byindex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ ) ; 

void test_refs_reflog_drop__can_drop_an_entry_and_rewrite_the_log_history(void)
{
	const git_reflog_entry *before_current;
	const git_reflog_entry *after_current;
	git_oid before_current_old_oid, before_current_cur_oid;

	cl_assert(entrycount > 4);

	before_current = git_reflog_entry_byindex(g_reflog, 1);

	git_oid_cpy(&before_current_old_oid, &before_current->oid_old);
	git_oid_cpy(&before_current_cur_oid, &before_current->oid_cur);

	cl_git_pass(git_reflog_drop(g_reflog, 1, 1));

	cl_assert_equal_sz(entrycount - 1, git_reflog_entrycount(g_reflog));

	after_current = git_reflog_entry_byindex(g_reflog, 0);

	cl_assert_equal_i(0, git_oid_cmp(&before_current_old_oid, &after_current->oid_old));
	cl_assert(0 != git_oid_cmp(&before_current_cur_oid, &after_current->oid_cur));
}