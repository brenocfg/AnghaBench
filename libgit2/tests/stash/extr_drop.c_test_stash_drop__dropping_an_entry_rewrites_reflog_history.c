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
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFS_STASH_FILE ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_reflog_entry_id_old (int /*<<< orphan*/  const*) ; 
 size_t git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_drop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_three_states () ; 
 int /*<<< orphan*/  repo ; 

void test_stash_drop__dropping_an_entry_rewrites_reflog_history(void)
{
	git_reference *stash;
	git_reflog *reflog;
	const git_reflog_entry *entry;
	git_oid oid;
	size_t count;

	push_three_states();

	cl_git_pass(git_reference_lookup(&stash, repo, GIT_REFS_STASH_FILE));

	cl_git_pass(git_reflog_read(&reflog, repo, GIT_REFS_STASH_FILE));
	entry = git_reflog_entry_byindex(reflog, 1);

	git_oid_cpy(&oid, git_reflog_entry_id_old(entry));
	count = git_reflog_entrycount(reflog);

	git_reflog_free(reflog);

	cl_git_pass(git_stash_drop(repo, 1));

	cl_git_pass(git_reflog_read(&reflog, repo, GIT_REFS_STASH_FILE));
	entry = git_reflog_entry_byindex(reflog, 0);

	cl_assert_equal_oid(&oid, git_reflog_entry_id_old(entry));
	cl_assert_equal_sz(count - 1, git_reflog_entrycount(reflog));

	git_reflog_free(reflog);

	git_reference_free(stash);
}