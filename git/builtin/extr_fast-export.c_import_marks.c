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
typedef  scalar_t__ uint32_t ;
struct stat {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int flags; } ;
struct commit {struct object object; } ;
typedef  int /*<<< orphan*/  line ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int OBJ_COMMIT ; 
 int SHOWN ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 scalar_t__ last_idnum ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  mark_object (struct object*,scalar_t__) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 char* oid_to_hex (struct object_id*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strtoumax (char*,char**,int) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/ * xfopen (char*,char*) ; 

__attribute__((used)) static void import_marks(char *input_file, int check_exists)
{
	char line[512];
	FILE *f;
	struct stat sb;

	if (check_exists && stat(input_file, &sb))
		return;

	f = xfopen(input_file, "r");
	while (fgets(line, sizeof(line), f)) {
		uint32_t mark;
		char *line_end, *mark_end;
		struct object_id oid;
		struct object *object;
		struct commit *commit;
		enum object_type type;

		line_end = strchr(line, '\n');
		if (line[0] != ':' || !line_end)
			die("corrupt mark line: %s", line);
		*line_end = '\0';

		mark = strtoumax(line + 1, &mark_end, 10);
		if (!mark || mark_end == line + 1
			|| *mark_end != ' ' || get_oid_hex(mark_end + 1, &oid))
			die("corrupt mark line: %s", line);

		if (last_idnum < mark)
			last_idnum = mark;

		type = oid_object_info(the_repository, &oid, NULL);
		if (type < 0)
			die("object not found: %s", oid_to_hex(&oid));

		if (type != OBJ_COMMIT)
			/* only commits */
			continue;

		commit = lookup_commit(the_repository, &oid);
		if (!commit)
			die("not a commit? can't happen: %s", oid_to_hex(&oid));

		object = &commit->object;

		if (object->flags & SHOWN)
			error("Object %s already has a mark", oid_to_hex(&oid));

		mark_object(object, mark);

		object->flags |= SHOWN;
	}
	fclose(f);
}