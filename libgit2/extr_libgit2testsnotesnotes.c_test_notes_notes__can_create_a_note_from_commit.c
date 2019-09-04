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
struct note_create_payload {char* member_0; char* member_1; int /*<<< orphan*/  object_oid; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _sig ; 
 int /*<<< orphan*/  assert_notes_seen (struct note_create_payload*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_note_foreach (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct note_create_payload**) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  note_list_create_cb ; 

void test_notes_notes__can_create_a_note_from_commit(void)
{
	git_oid oid;
	git_oid notes_commit_out;
	git_reference *ref;
	static struct note_create_payload can_create_a_note_from_commit[] = {
		{ "1c9b1bc36730582a42d56eeee0dc58673d7ae869", "4a202b346bb0fb0db7eff3cffeb3c70babbd2045", 0 },
		{ NULL, NULL, 0 }
	};

	cl_git_pass(git_oid_fromstr(&oid, can_create_a_note_from_commit[0].object_oid));

	cl_git_pass(git_note_commit_create(&notes_commit_out, NULL, _repo, NULL, _sig, _sig, &oid, "I decorate 4a20\n", 1));

	/* create_from_commit will not update any ref,
	 * so we must manually create the ref, that points to the commit */
	cl_git_pass(git_reference_create(&ref, _repo, "refs/notes/i-can-see-dead-notes", &notes_commit_out, 0, NULL));

	cl_git_pass(git_note_foreach(_repo, "refs/notes/i-can-see-dead-notes", note_list_create_cb, &can_create_a_note_from_commit));

	assert_notes_seen(can_create_a_note_from_commit, 1);

	git_reference_free(ref);
}