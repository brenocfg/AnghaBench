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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_note (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_remove (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__can_remove_a_note(void)
{
	git_oid note_oid, target_oid;
	git_note *note;

	create_note(&note_oid, "refs/notes/i-can-see-dead-notes", "4a202b346bb0fb0db7eff3cffeb3c70babbd2045", "I decorate 4a20\n");

	cl_git_pass(git_oid_fromstr(&target_oid, "4a202b346bb0fb0db7eff3cffeb3c70babbd2045"));
	cl_git_pass(git_note_remove(_repo, "refs/notes/i-can-see-dead-notes", _sig, _sig, &target_oid));

	cl_git_fail(git_note_read(&note, _repo, "refs/notes/i-can-see-dead-notes", &target_oid));
}