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
struct notes_tree {scalar_t__ dirty; } ;
struct notes_merge_pair {int dummy; } ;
struct notes_merge_options {int verbosity; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_tree_local (struct notes_merge_options*,struct notes_merge_pair*,int,struct object_id const*,struct object_id const*) ; 
 struct notes_merge_pair* diff_tree_remote (struct notes_merge_options*,struct object_id const*,struct object_id const*,int*) ; 
 int /*<<< orphan*/  free (struct notes_merge_pair*) ; 
 int merge_changes (struct notes_merge_options*,struct notes_merge_pair*,int*,struct notes_tree*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  trace_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int merge_from_diffs(struct notes_merge_options *o,
			    const struct object_id *base,
			    const struct object_id *local,
			    const struct object_id *remote,
			    struct notes_tree *t)
{
	struct notes_merge_pair *changes;
	int num_changes, conflicts;

	trace_printf("\tmerge_from_diffs(base = %.7s, local = %.7s, "
	       "remote = %.7s)\n", oid_to_hex(base), oid_to_hex(local),
	       oid_to_hex(remote));

	changes = diff_tree_remote(o, base, remote, &num_changes);
	diff_tree_local(o, changes, num_changes, base, local);

	conflicts = merge_changes(o, changes, &num_changes, t);
	free(changes);

	if (o->verbosity >= 4)
		printf(t->dirty ?
		       "Merge result: %i unmerged notes and a dirty notes tree\n" :
		       "Merge result: %i unmerged notes and a clean notes tree\n",
		       conflicts);

	return conflicts ? -1 : 1;
}