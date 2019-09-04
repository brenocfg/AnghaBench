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
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (char*) ; 
 int OBJ_BLOB ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_notes (int /*<<< orphan*/ *) ; 
 struct object_id* get_note (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  init_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notes_ref ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 

__attribute__((used)) static char *read_ref_note(const struct object_id *oid)
{
	const struct object_id *note_oid;
	char *msg = NULL;
	unsigned long msglen;
	enum object_type type;

	init_notes(NULL, notes_ref, NULL, 0);
	if (!(note_oid = get_note(NULL, oid)))
		return NULL;	/* note tree not found */
	if (!(msg = read_object_file(note_oid, &type, &msglen)))
		error("Empty notes tree. %s", notes_ref);
	else if (!msglen || type != OBJ_BLOB) {
		error("Note contains unusable content. "
			"Is something else using this notes tree? %s", notes_ref);
		FREE_AND_NULL(msg);
	}
	free_notes(NULL);
	return msg;
}