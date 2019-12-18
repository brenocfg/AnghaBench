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
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct test_entry {char* name; TYPE_1__ entry; } ;
struct strbuf {int /*<<< orphan*/ * buf; } ;
struct oidmap_iter {int dummy; } ;
struct oidmap {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELIM ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct test_entry*,int /*<<< orphan*/ ,char*) ; 
 struct oidmap OIDMAP_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (struct test_entry*) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  name ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  oidmap_free (struct oidmap*,int) ; 
 struct test_entry* oidmap_get (struct oidmap*,struct object_id*) ; 
 int /*<<< orphan*/  oidmap_init (struct oidmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidmap_iter_init (struct oidmap*,struct oidmap_iter*) ; 
 struct test_entry* oidmap_iter_next (struct oidmap_iter*) ; 
 struct test_entry* oidmap_put (struct oidmap*,struct test_entry*) ; 
 struct test_entry* oidmap_remove (struct oidmap*,struct object_id*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strtok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cmd__oidmap(int argc, const char **argv)
{
	struct strbuf line = STRBUF_INIT;
	struct oidmap map = OIDMAP_INIT;

	setup_git_directory();

	/* init oidmap */
	oidmap_init(&map, 0);

	/* process commands from stdin */
	while (strbuf_getline(&line, stdin) != EOF) {
		char *cmd, *p1 = NULL, *p2 = NULL;
		struct test_entry *entry;
		struct object_id oid;

		/* break line into command and up to two parameters */
		cmd = strtok(line.buf, DELIM);
		/* ignore empty lines */
		if (!cmd || *cmd == '#')
			continue;

		p1 = strtok(NULL, DELIM);
		if (p1)
			p2 = strtok(NULL, DELIM);

		if (!strcmp("put", cmd) && p1 && p2) {

			if (get_oid(p1, &oid)) {
				printf("Unknown oid: %s\n", p1);
				continue;
			}

			/* create entry with oid_key = p1, name_value = p2 */
			FLEX_ALLOC_STR(entry, name, p2);
			oidcpy(&entry->entry.oid, &oid);

			/* add / replace entry */
			entry = oidmap_put(&map, entry);

			/* print and free replaced entry, if any */
			puts(entry ? entry->name : "NULL");
			free(entry);

		} else if (!strcmp("get", cmd) && p1) {

			if (get_oid(p1, &oid)) {
				printf("Unknown oid: %s\n", p1);
				continue;
			}

			/* lookup entry in oidmap */
			entry = oidmap_get(&map, &oid);

			/* print result */
			puts(entry ? entry->name : "NULL");

		} else if (!strcmp("remove", cmd) && p1) {

			if (get_oid(p1, &oid)) {
				printf("Unknown oid: %s\n", p1);
				continue;
			}

			/* remove entry from oidmap */
			entry = oidmap_remove(&map, &oid);

			/* print result and free entry*/
			puts(entry ? entry->name : "NULL");
			free(entry);

		} else if (!strcmp("iterate", cmd)) {

			struct oidmap_iter iter;
			oidmap_iter_init(&map, &iter);
			while ((entry = oidmap_iter_next(&iter)))
				printf("%s %s\n", oid_to_hex(&entry->entry.oid), entry->name);

		} else {

			printf("Unknown command %s\n", cmd);

		}
	}

	strbuf_release(&line);
	oidmap_free(&map, 1);
	return 0;
}