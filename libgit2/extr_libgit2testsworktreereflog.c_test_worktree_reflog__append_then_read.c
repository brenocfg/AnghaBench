#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_4__ {int /*<<< orphan*/  oid_cur; int /*<<< orphan*/  oid_old; } ;
typedef  TYPE_1__ git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {int /*<<< orphan*/  repo; int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFLOG ; 
 int /*<<< orphan*/  REFLOG_MESSAGE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_3__ fixture ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_append (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 

void test_worktree_reflog__append_then_read(void)
{
	git_reflog *reflog, *parent_reflog;
	const git_reflog_entry *entry;
	git_reference *head;
	git_signature *sig;
	const git_oid *oid;

	cl_git_pass(git_repository_head(&head, fixture.worktree));
	cl_assert((oid = git_reference_target(head)) != NULL);
	cl_git_pass(git_signature_now(&sig, "foo", "foo@bar"));

	cl_git_pass(git_reflog_read(&reflog, fixture.worktree, REFLOG));
	cl_git_pass(git_reflog_append(reflog, oid, sig, REFLOG_MESSAGE));
	git_reflog_write(reflog);

	cl_git_pass(git_reflog_read(&parent_reflog, fixture.repo, REFLOG));
	entry = git_reflog_entry_byindex(parent_reflog, 0);
	cl_assert(git_oid_cmp(oid, &entry->oid_old) == 0);
	cl_assert(git_oid_cmp(oid, &entry->oid_cur) == 0);

	git_reference_free(head);
	git_signature_free(sig);
	git_reflog_free(reflog);
	git_reflog_free(parent_reflog);
}