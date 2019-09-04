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
 size_t MESSAGES_COUNT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * messages ; 

void test_notes_notes__can_insert_a_note_in_an_existing_fanout(void)
{
	size_t i;
	git_oid note_oid, target_oid;
	git_note *_note;

	cl_git_pass(git_oid_fromstr(&target_oid, "08b041783f40edfe12bb406c9c9a8a040177c125"));
	
	for (i = 0; i <  MESSAGES_COUNT; i++) {
		cl_git_pass(git_note_create(&note_oid, _repo, "refs/notes/fanout", _sig, _sig, &target_oid, messages[i], 0));
		cl_git_pass(git_note_read(&_note, _repo, "refs/notes/fanout", &target_oid));
		git_note_free(_note);

		git_oid_cpy(&target_oid, &note_oid);
	}
}