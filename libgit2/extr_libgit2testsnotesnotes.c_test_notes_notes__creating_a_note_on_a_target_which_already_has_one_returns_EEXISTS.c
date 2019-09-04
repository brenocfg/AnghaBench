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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_note (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int git_note_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__creating_a_note_on_a_target_which_already_has_one_returns_EEXISTS(void)
{
	int error;
	git_oid note_oid, target_oid;

	cl_git_pass(git_oid_fromstr(&target_oid, "08b041783f40edfe12bb406c9c9a8a040177c125"));

	create_note(&note_oid, NULL, "08b041783f40edfe12bb406c9c9a8a040177c125", "hello world\n");
	error = git_note_create(&note_oid, _repo, NULL, _sig, _sig, &target_oid, "hello world\n", 0);
	cl_git_fail(error);
	cl_assert_equal_i(GIT_EEXISTS, error);

	create_note(&note_oid, "refs/notes/some/namespace", "08b041783f40edfe12bb406c9c9a8a040177c125", "hello world\n");
	error = git_note_create(&note_oid, _repo, "refs/notes/some/namespace", _sig, _sig, &target_oid, "hello world\n", 0);
	cl_git_fail(error);
	cl_assert_equal_i(GIT_EEXISTS, error);
}