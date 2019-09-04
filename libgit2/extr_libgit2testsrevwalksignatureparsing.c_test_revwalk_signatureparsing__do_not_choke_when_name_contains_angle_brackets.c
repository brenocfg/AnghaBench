#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int offset; scalar_t__ time; } ;
struct TYPE_5__ {TYPE_1__ when; int /*<<< orphan*/  name; int /*<<< orphan*/  email; } ;
typedef  TYPE_2__ git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_2__* git_commit_committer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_revwalk_signatureparsing__do_not_choke_when_name_contains_angle_brackets(void)
{
	git_reference *ref;
	git_oid commit_oid;
	git_commit *commit;
	const git_signature *signature;

	/*
	 * The branch below points at a commit with angle brackets in the committer/author name
	 * committer <Yu V. Bin Haacked> <foo@example.com> 1323847743 +0100
	 */
	cl_git_pass(git_reference_lookup(&ref, _repo, "refs/heads/haacked"));

	git_revwalk_push(_walk, git_reference_target(ref));
	cl_git_pass(git_revwalk_next(&commit_oid, _walk));

	cl_git_pass(git_commit_lookup(&commit, _repo, git_reference_target(ref)));

	signature = git_commit_committer(commit);
	cl_assert_equal_s("foo@example.com", signature->email);
	cl_assert_equal_s("Yu V. Bin Haacked", signature->name);
	cl_assert_equal_i(1323847743, (int)signature->when.time);
	cl_assert_equal_i(60, signature->when.offset);

	git_commit_free(commit);
	git_reference_free(ref);
}