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
struct strbuf {char const* buf; } ;
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct oid_array OID_ARRAY_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id*) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int /*<<< orphan*/  oid_array_for_each_unique (struct oid_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int oid_array_lookup (struct oid_array*,struct object_id*) ; 
 int /*<<< orphan*/  print_oid ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int cmd__sha1_array(int argc, const char **argv)
{
	struct oid_array array = OID_ARRAY_INIT;
	struct strbuf line = STRBUF_INIT;

	while (strbuf_getline(&line, stdin) != EOF) {
		const char *arg;
		struct object_id oid;

		if (skip_prefix(line.buf, "append ", &arg)) {
			if (get_oid_hex(arg, &oid))
				die("not a hexadecimal SHA1: %s", arg);
			oid_array_append(&array, &oid);
		} else if (skip_prefix(line.buf, "lookup ", &arg)) {
			if (get_oid_hex(arg, &oid))
				die("not a hexadecimal SHA1: %s", arg);
			printf("%d\n", oid_array_lookup(&array, &oid));
		} else if (!strcmp(line.buf, "clear"))
			oid_array_clear(&array);
		else if (!strcmp(line.buf, "for_each_unique"))
			oid_array_for_each_unique(&array, print_oid, NULL);
		else
			die("unknown command: %s", line.buf);
	}
	return 0;
}