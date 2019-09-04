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
typedef  int /*<<< orphan*/  git_note ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_note_commit_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_commit_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__attempt_to_read_a_note_from_a_commit_with_no_note_fails(void)
{
	git_oid oid, notes_commit_oid;
	git_commit *notes_commit;
	git_note *note;

	cl_git_pass(git_oid_fromstr(&oid, "4a202b346bb0fb0db7eff3cffeb3c70babbd2045"));

	cl_git_pass(git_note_commit_create(&notes_commit_oid, NULL, _repo, NULL, _sig, _sig, &oid, "I decorate 4a20\n", 1));

	git_commit_lookup(&notes_commit, _repo, &notes_commit_oid);

	cl_git_pass(git_note_commit_remove(&notes_commit_oid, _repo, notes_commit, _sig, _sig, &oid));
	git_commit_free(notes_commit);

	git_commit_lookup(&notes_commit, _repo, &notes_commit_oid);

	cl_assert(notes_commit);

	cl_git_fail_with(GIT_ENOTFOUND, git_note_commit_read(&note, _repo, notes_commit, &oid));

	git_commit_free(notes_commit);
}