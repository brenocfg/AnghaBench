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
 int OBJ_BLOB ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  write_buf_to_worktree (struct object_id const*,void*,unsigned long) ; 

__attribute__((used)) static void write_note_to_worktree(const struct object_id *obj,
				   const struct object_id *note)
{
	enum object_type type;
	unsigned long size;
	void *buf = read_object_file(note, &type, &size);

	if (!buf)
		die("cannot read note %s for object %s",
		    oid_to_hex(note), oid_to_hex(obj));
	if (type != OBJ_BLOB)
		die("blob expected in note %s for object %s",
		    oid_to_hex(note), oid_to_hex(obj));
	write_buf_to_worktree(obj, buf, size);
	free(buf);
}