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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int git_note_remove (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__removing_a_note_which_doesnt_exists_returns_ENOTFOUND(void)
{
	int error;
	git_oid target_oid;

	cl_git_pass(git_oid_fromstr(&target_oid, "8496071c1b46c854b31185ea97743be6a8774479"));
	cl_git_pass(git_note_remove(_repo, "refs/notes/fanout", _sig, _sig, &target_oid));
	
	error = git_note_remove(_repo, "refs/notes/fanout", _sig, _sig, &target_oid);
	cl_git_fail(error);
	cl_assert_equal_i(GIT_ENOTFOUND, error);
}