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
typedef  int /*<<< orphan*/  git_note_iterator ;
typedef  int /*<<< orphan*/  git_note ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_commit_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_commit_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_message (int /*<<< orphan*/ *) ; 
 int git_note_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__iterate_from_commit(void)
{
	git_note_iterator *iter;
	git_note *note;
	git_oid note_id, annotated_id;
	git_oid oids[2];
	git_oid notes_commit_oids[2];
	git_commit *notes_commits[2];
	const char* note_message[] = {
		"I decorate a65f\n",
		"I decorate c478\n"
	};
	int i, err;

	cl_git_pass(git_oid_fromstr(&(oids[0]), "a65fedf39aefe402d3bb6e24df4d4f5fe4547750"));
	cl_git_pass(git_oid_fromstr(&(oids[1]), "c47800c7266a2be04c571c04d5a6614691ea99bd"));

	cl_git_pass(git_note_commit_create(&notes_commit_oids[0], NULL, _repo, NULL, _sig, _sig, &(oids[0]), note_message[0], 0));

	git_commit_lookup(&notes_commits[0], _repo, &notes_commit_oids[0]);
	cl_assert(notes_commits[0]);

	cl_git_pass(git_note_commit_create(&notes_commit_oids[1], NULL, _repo, notes_commits[0], _sig, _sig, &(oids[1]), note_message[1], 0));

	git_commit_lookup(&notes_commits[1], _repo, &notes_commit_oids[1]);
	cl_assert(notes_commits[1]);

	cl_git_pass(git_note_commit_iterator_new(&iter, notes_commits[1]));

	for (i = 0; (err = git_note_next(&note_id, &annotated_id, iter)) >= 0; ++i) {
		cl_git_pass(git_note_commit_read(&note, _repo, notes_commits[1], &annotated_id));
		cl_assert_equal_s(git_note_message(note), note_message[i]);
		git_note_free(note);
	}

	cl_assert_equal_i(GIT_ITEROVER, err);
	cl_assert_equal_i(2, i);

	git_note_iterator_free(iter);
	git_commit_free(notes_commits[0]);
	git_commit_free(notes_commits[1]);
}