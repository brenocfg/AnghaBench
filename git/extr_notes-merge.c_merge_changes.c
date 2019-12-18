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
struct notes_tree {int dummy; } ;
struct notes_merge_pair {int /*<<< orphan*/  remote; int /*<<< orphan*/  obj; int /*<<< orphan*/  base; int /*<<< orphan*/  local; } ;
struct notes_merge_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ add_note (struct notes_tree*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  combine_notes_overwrite ; 
 scalar_t__ merge_one_change (struct notes_merge_options*,struct notes_merge_pair*,struct notes_tree*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_printf (char*,...) ; 
 int /*<<< orphan*/  uninitialized ; 

__attribute__((used)) static int merge_changes(struct notes_merge_options *o,
			 struct notes_merge_pair *changes, int *num_changes,
			 struct notes_tree *t)
{
	int i, conflicts = 0;

	trace_printf("\tmerge_changes(num_changes = %i)\n", *num_changes);
	for (i = 0; i < *num_changes; i++) {
		struct notes_merge_pair *p = changes + i;
		trace_printf("\t\t%.7s: %.7s -> %.7s/%.7s\n",
		       oid_to_hex(&p->obj), oid_to_hex(&p->base),
		       oid_to_hex(&p->local),
		       oid_to_hex(&p->remote));

		if (oideq(&p->base, &p->remote)) {
			/* no remote change; nothing to do */
			trace_printf("\t\t\tskipping (no remote change)\n");
		} else if (oideq(&p->local, &p->remote)) {
			/* same change in local and remote; nothing to do */
			trace_printf("\t\t\tskipping (local == remote)\n");
		} else if (oideq(&p->local, &uninitialized) ||
			   oideq(&p->local, &p->base)) {
			/* no local change; adopt remote change */
			trace_printf("\t\t\tno local change, adopted remote\n");
			if (add_note(t, &p->obj, &p->remote,
				     combine_notes_overwrite))
				BUG("combine_notes_overwrite failed");
		} else {
			/* need file-level merge between local and remote */
			trace_printf("\t\t\tneed content-level merge\n");
			conflicts += merge_one_change(o, p, t);
		}
	}

	return conflicts;
}