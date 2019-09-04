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
struct note_create_payload {int seen; int /*<<< orphan*/ * object_oid; int /*<<< orphan*/ * note_oid; } ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fail (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int note_list_create_cb(
	const git_oid *blob_oid, const git_oid *annotated_obj_id, void *payload)
{
	git_oid expected_note_oid, expected_target_oid;
	struct note_create_payload *notes = payload;
	size_t i;

	for (i = 0; notes[i].note_oid != NULL; i++) {
		cl_git_pass(git_oid_fromstr(&expected_note_oid, notes[i].note_oid));

		if (git_oid_cmp(&expected_note_oid, blob_oid) != 0)
			continue;

		cl_git_pass(git_oid_fromstr(&expected_target_oid, notes[i].object_oid));

		if (git_oid_cmp(&expected_target_oid, annotated_obj_id) != 0)
			continue;

		notes[i].seen = 1;
		return 0;
	}

	cl_fail("Did not see expected note");
	return 0;
}