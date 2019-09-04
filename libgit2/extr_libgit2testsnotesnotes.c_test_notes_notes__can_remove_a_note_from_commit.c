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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_commit_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 

void test_notes_notes__can_remove_a_note_from_commit(void)
{
	git_oid oid, notes_commit_oid;
	git_note *note = NULL;
	git_commit *existing_notes_commit;
	git_reference *ref;

	cl_git_pass(git_oid_fromstr(&oid, "4a202b346bb0fb0db7eff3cffeb3c70babbd2045"));

	cl_git_pass(git_note_commit_create(&notes_commit_oid, NULL, _repo, NULL, _sig, _sig, &oid, "I decorate 4a20\n", 0));

	git_commit_lookup(&existing_notes_commit, _repo, &notes_commit_oid);

	cl_assert(existing_notes_commit);

	cl_git_pass(git_note_commit_remove(&notes_commit_oid, _repo, existing_notes_commit, _sig, _sig, &oid));

	/* remove_from_commit will not update any ref,
	 * so we must manually create the ref, that points to the commit */
	cl_git_pass(git_reference_create(&ref, _repo, "refs/notes/i-can-see-dead-notes", &notes_commit_oid, 0, NULL));

	cl_git_fail(git_note_read(&note, _repo, "refs/notes/i-can-see-dead-notes", &oid));

	git_commit_free(existing_notes_commit);
	git_reference_free(ref);
	git_note_free(note);
}