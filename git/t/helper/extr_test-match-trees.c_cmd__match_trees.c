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
struct tree {TYPE_1__ object; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 char* oid_to_hex (struct object_id*) ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int /*<<< orphan*/  shift_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct object_id*,int) ; 
 int /*<<< orphan*/  the_repository ; 

int cmd__match_trees(int ac, const char **av)
{
	struct object_id hash1, hash2, shifted;
	struct tree *one, *two;

	setup_git_directory();

	if (get_oid(av[1], &hash1))
		die("cannot parse %s as an object name", av[1]);
	if (get_oid(av[2], &hash2))
		die("cannot parse %s as an object name", av[2]);
	one = parse_tree_indirect(&hash1);
	if (!one)
		die("not a tree-ish %s", av[1]);
	two = parse_tree_indirect(&hash2);
	if (!two)
		die("not a tree-ish %s", av[2]);

	shift_tree(the_repository, &one->object.oid, &two->object.oid, &shifted, -1);
	printf("shifted: %s\n", oid_to_hex(&shifted));

	exit(0);
}