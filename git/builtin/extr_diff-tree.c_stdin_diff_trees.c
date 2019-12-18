#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct object_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  diffopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int error (char*) ; 
 int /*<<< orphan*/  isspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_tree_diff_flush (TYPE_2__*) ; 
 TYPE_2__ log_tree_opt ; 
 struct tree* lookup_tree (int /*<<< orphan*/ ,struct object_id*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 scalar_t__ parse_tree (struct tree*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int stdin_diff_trees(struct tree *tree1, const char *p)
{
	struct object_id oid;
	struct tree *tree2;
	if (!isspace(*p++) || parse_oid_hex(p, &oid, &p) || *p)
		return error("Need exactly two trees, separated by a space");
	tree2 = lookup_tree(the_repository, &oid);
	if (!tree2 || parse_tree(tree2))
		return -1;
	printf("%s %s\n", oid_to_hex(&tree1->object.oid),
			  oid_to_hex(&tree2->object.oid));
	diff_tree_oid(&tree1->object.oid, &tree2->object.oid,
		      "", &log_tree_opt.diffopt);
	log_tree_diff_flush(&log_tree_opt);
	return 0;
}