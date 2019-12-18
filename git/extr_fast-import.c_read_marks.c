#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int offset; } ;
struct object_entry {int type; TYPE_1__ idx; int /*<<< orphan*/  pack_id; } ;
typedef  int /*<<< orphan*/  line ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  MAX_PACK_ID ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 struct object_entry* find_object (struct object_id*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 int /*<<< orphan*/  import_marks_file ; 
 int import_marks_file_done ; 
 scalar_t__ import_marks_file_ignore_missing ; 
 int /*<<< orphan*/  insert_mark (int /*<<< orphan*/ ,struct object_entry*) ; 
 struct object_entry* insert_object (struct object_id*) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 char* oid_to_hex (struct object_id*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strtoumax (char*,char**,int) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void read_marks(void)
{
	char line[512];
	FILE *f = fopen(import_marks_file, "r");
	if (f)
		;
	else if (import_marks_file_ignore_missing && errno == ENOENT)
		goto done; /* Marks file does not exist */
	else
		die_errno("cannot read '%s'", import_marks_file);
	while (fgets(line, sizeof(line), f)) {
		uintmax_t mark;
		char *end;
		struct object_id oid;
		struct object_entry *e;

		end = strchr(line, '\n');
		if (line[0] != ':' || !end)
			die("corrupt mark line: %s", line);
		*end = 0;
		mark = strtoumax(line + 1, &end, 10);
		if (!mark || end == line + 1
			|| *end != ' ' || get_oid_hex(end + 1, &oid))
			die("corrupt mark line: %s", line);
		e = find_object(&oid);
		if (!e) {
			enum object_type type = oid_object_info(the_repository,
								&oid, NULL);
			if (type < 0)
				die("object not found: %s", oid_to_hex(&oid));
			e = insert_object(&oid);
			e->type = type;
			e->pack_id = MAX_PACK_ID;
			e->idx.offset = 1; /* just not zero! */
		}
		insert_mark(mark, e);
	}
	fclose(f);
done:
	import_marks_file_done = 1;
}