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
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__can_read_a_note_in_an_existing_fanout(void)
{
	git_oid note_oid, target_oid;
	git_note *note;

	cl_git_pass(git_oid_fromstr(&target_oid, "8496071c1b46c854b31185ea97743be6a8774479"));
	cl_git_pass(git_note_read(&note, _repo, "refs/notes/fanout", &target_oid));

	cl_git_pass(git_oid_fromstr(&note_oid, "08b041783f40edfe12bb406c9c9a8a040177c125"));
	cl_assert_equal_oid(git_note_id(note), &note_oid);

	git_note_free(note);
}