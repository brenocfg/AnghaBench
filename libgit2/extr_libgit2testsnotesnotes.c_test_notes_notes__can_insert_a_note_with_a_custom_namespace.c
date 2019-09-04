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
 int /*<<< orphan*/  assert_note_equal (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_note (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__can_insert_a_note_with_a_custom_namespace(void)
{
	git_oid note_oid, target_oid;
	git_note *note;

	cl_git_pass(git_oid_fromstr(&target_oid, "08b041783f40edfe12bb406c9c9a8a040177c125"));

	create_note(&note_oid, "refs/notes/some/namespace", "08b041783f40edfe12bb406c9c9a8a040177c125", "hello world on a custom namespace\n");

	cl_git_pass(git_note_read(&note, _repo, "refs/notes/some/namespace", &target_oid));

	assert_note_equal(note, "hello world on a custom namespace\n", &note_oid);

	git_note_free(note);
}