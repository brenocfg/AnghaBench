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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_notes_seen (struct note_create_payload*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_note (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_note_foreach (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct note_create_payload**) ; 
 int /*<<< orphan*/  note_list_create_cb ; 

void test_notes_notes__can_create_a_note(void)
{
	git_oid note_oid;
	static struct note_create_payload can_create_a_note[] = {
		{ "1c9b1bc36730582a42d56eeee0dc58673d7ae869", "4a202b346bb0fb0db7eff3cffeb3c70babbd2045", 0 },
		{ NULL, NULL, 0 }
	};

	create_note(&note_oid, "refs/notes/i-can-see-dead-notes", can_create_a_note[0].object_oid, "I decorate 4a20\n");

	cl_git_pass(git_note_foreach(_repo, "refs/notes/i-can-see-dead-notes", note_list_create_cb, &can_create_a_note));

	assert_notes_seen(can_create_a_note, 1);
}