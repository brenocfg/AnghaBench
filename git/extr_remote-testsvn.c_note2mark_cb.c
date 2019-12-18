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
struct rev_note {int rev_nr; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int fprintf (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* oid_to_hex (struct object_id const*) ; 
 scalar_t__ parse_rev_note (char*,struct rev_note*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 

__attribute__((used)) static int note2mark_cb(const struct object_id *object_oid,
		const struct object_id *note_oid, char *note_path,
		void *cb_data)
{
	FILE *file = (FILE *)cb_data;
	char *msg;
	unsigned long msglen;
	enum object_type type;
	struct rev_note note;

	if (!(msg = read_object_file(note_oid, &type, &msglen)) ||
			!msglen || type != OBJ_BLOB) {
		free(msg);
		return 1;
	}
	if (parse_rev_note(msg, &note))
		return 2;
	if (fprintf(file, ":%d %s\n", note.rev_nr, oid_to_hex(object_oid)) < 1)
		return 3;
	return 0;
}