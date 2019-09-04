#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct notes_tree {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  hash; } ;
struct notes_merge_pair {TYPE_1__ obj; TYPE_1__ remote; TYPE_1__ local; TYPE_1__ base; } ;
struct notes_merge_options {char* local_ref; char* remote_ref; int verbosity; int /*<<< orphan*/  commit_msg; int /*<<< orphan*/  has_worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_notes_merge_worktree (struct notes_merge_options*) ; 
 scalar_t__ is_null_oid (TYPE_1__*) ; 
 int /*<<< orphan*/  ll_merge_in_worktree (struct notes_merge_options*,struct notes_merge_pair*) ; 
 char* oid_to_hex (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  remove_note (struct notes_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  trace_printf (char*,...) ; 
 int /*<<< orphan*/  write_note_to_worktree (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int merge_one_change_manual(struct notes_merge_options *o,
				   struct notes_merge_pair *p,
				   struct notes_tree *t)
{
	const char *lref = o->local_ref ? o->local_ref : "local version";
	const char *rref = o->remote_ref ? o->remote_ref : "remote version";

	trace_printf("\t\t\tmerge_one_change_manual(obj = %.7s, base = %.7s, "
	       "local = %.7s, remote = %.7s)\n",
	       oid_to_hex(&p->obj), oid_to_hex(&p->base),
	       oid_to_hex(&p->local), oid_to_hex(&p->remote));

	/* add "Conflicts:" section to commit message first time through */
	if (!o->has_worktree)
		strbuf_addstr(&(o->commit_msg), "\n\nConflicts:\n");

	strbuf_addf(&(o->commit_msg), "\t%s\n", oid_to_hex(&p->obj));

	if (o->verbosity >= 2)
		printf("Auto-merging notes for %s\n", oid_to_hex(&p->obj));
	check_notes_merge_worktree(o);
	if (is_null_oid(&p->local)) {
		/* D/F conflict, checkout p->remote */
		assert(!is_null_oid(&p->remote));
		if (o->verbosity >= 1)
			printf("CONFLICT (delete/modify): Notes for object %s "
				"deleted in %s and modified in %s. Version from %s "
				"left in tree.\n",
				oid_to_hex(&p->obj), lref, rref, rref);
		write_note_to_worktree(&p->obj, &p->remote);
	} else if (is_null_oid(&p->remote)) {
		/* D/F conflict, checkout p->local */
		assert(!is_null_oid(&p->local));
		if (o->verbosity >= 1)
			printf("CONFLICT (delete/modify): Notes for object %s "
				"deleted in %s and modified in %s. Version from %s "
				"left in tree.\n",
				oid_to_hex(&p->obj), rref, lref, lref);
		write_note_to_worktree(&p->obj, &p->local);
	} else {
		/* "regular" conflict, checkout result of ll_merge() */
		const char *reason = "content";
		if (is_null_oid(&p->base))
			reason = "add/add";
		assert(!is_null_oid(&p->local));
		assert(!is_null_oid(&p->remote));
		if (o->verbosity >= 1)
			printf("CONFLICT (%s): Merge conflict in notes for "
				"object %s\n", reason,
				oid_to_hex(&p->obj));
		ll_merge_in_worktree(o, p);
	}

	trace_printf("\t\t\tremoving from partial merge result\n");
	remove_note(t, p->obj.hash);

	return 1;
}