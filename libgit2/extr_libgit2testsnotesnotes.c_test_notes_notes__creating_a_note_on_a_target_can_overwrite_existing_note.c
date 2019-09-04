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

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  assert_note_equal (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_note (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  git_note_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__creating_a_note_on_a_target_can_overwrite_existing_note(void)
{
	git_oid note_oid, target_oid;
	git_note *note, *namespace_note;

	cl_git_pass(git_oid_fromstr(&target_oid, "08b041783f40edfe12bb406c9c9a8a040177c125"));

	create_note(&note_oid, NULL, "08b041783f40edfe12bb406c9c9a8a040177c125", "hello old world\n");
	cl_git_pass(git_note_create(&note_oid, _repo, NULL, _sig, _sig, &target_oid, "hello new world\n", 1));

	cl_git_pass(git_note_read(&note, _repo, NULL, &target_oid));
	assert_note_equal(note, "hello new world\n", &note_oid);

	create_note(&note_oid, "refs/notes/some/namespace", "08b041783f40edfe12bb406c9c9a8a040177c125", "hello old world\n");
	cl_git_pass(git_note_create(&note_oid, _repo, "refs/notes/some/namespace", _sig, _sig, &target_oid, "hello new ref world\n", 1));

	cl_git_pass(git_note_read(&namespace_note, _repo, "refs/notes/some/namespace", &target_oid));
	assert_note_equal(namespace_note, "hello new ref world\n", &note_oid);

	git_note_free(note);
	git_note_free(namespace_note);
}