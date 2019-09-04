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

/* Variables and functions */
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  test_get_commit_tree_in_graph (char const*,char const*,struct object_id*) ; 
 int /*<<< orphan*/  test_parse_commit_in_graph (char const*,char const*,struct object_id*) ; 

int cmd__repository(int argc, const char **argv)
{
	if (argc < 2)
		die("must have at least 2 arguments");
	if (!strcmp(argv[1], "parse_commit_in_graph")) {
		struct object_id oid;
		if (argc < 5)
			die("not enough arguments");
		if (parse_oid_hex(argv[4], &oid, &argv[4]))
			die("cannot parse oid '%s'", argv[4]);
		test_parse_commit_in_graph(argv[2], argv[3], &oid);
	} else if (!strcmp(argv[1], "get_commit_tree_in_graph")) {
		struct object_id oid;
		if (argc < 5)
			die("not enough arguments");
		if (parse_oid_hex(argv[4], &oid, &argv[4]))
			die("cannot parse oid '%s'", argv[4]);
		test_get_commit_tree_in_graph(argv[2], argv[3], &oid);
	} else {
		die("unrecognized '%s'", argv[1]);
	}
	return 0;
}