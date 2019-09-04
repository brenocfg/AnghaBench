#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct pretty_print_context {int dummy; } ;
struct object_id {int dummy; } ;
struct notes_tree {int dummy; } ;
struct notes_merge_options {void* local_ref; } ;
struct commit {TYPE_3__* parents; } ;
typedef  int /*<<< orphan*/  pretty_ctx ;
struct TYPE_6__ {TYPE_2__* item; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {TYPE_1__ object; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  combine_notes_overwrite ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_commit_message (struct commit*,char*,struct strbuf*,struct pretty_print_context*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  free_notes (struct notes_tree*) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  init_notes (struct notes_tree*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  memset (struct pretty_print_context*,int /*<<< orphan*/ ,int) ; 
 int merge_abort (struct notes_merge_options*) ; 
 scalar_t__ notes_merge_commit (struct notes_merge_options*,struct notes_tree*,struct commit*,struct object_id*) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 void* resolve_refdup (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  update_ref (int /*<<< orphan*/ ,void*,struct object_id*,struct object_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct notes_tree* xcalloc (int,int) ; 

__attribute__((used)) static int merge_commit(struct notes_merge_options *o)
{
	struct strbuf msg = STRBUF_INIT;
	struct object_id oid, parent_oid;
	struct notes_tree *t;
	struct commit *partial;
	struct pretty_print_context pretty_ctx;
	void *local_ref_to_free;
	int ret;

	/*
	 * Read partial merge result from .git/NOTES_MERGE_PARTIAL,
	 * and target notes ref from .git/NOTES_MERGE_REF.
	 */

	if (get_oid("NOTES_MERGE_PARTIAL", &oid))
		die(_("failed to read ref NOTES_MERGE_PARTIAL"));
	else if (!(partial = lookup_commit_reference(the_repository, &oid)))
		die(_("could not find commit from NOTES_MERGE_PARTIAL."));
	else if (parse_commit(partial))
		die(_("could not parse commit from NOTES_MERGE_PARTIAL."));

	if (partial->parents)
		oidcpy(&parent_oid, &partial->parents->item->object.oid);
	else
		oidclr(&parent_oid);

	t = xcalloc(1, sizeof(struct notes_tree));
	init_notes(t, "NOTES_MERGE_PARTIAL", combine_notes_overwrite, 0);

	o->local_ref = local_ref_to_free =
		resolve_refdup("NOTES_MERGE_REF", 0, &oid, NULL);
	if (!o->local_ref)
		die(_("failed to resolve NOTES_MERGE_REF"));

	if (notes_merge_commit(o, t, partial, &oid))
		die(_("failed to finalize notes merge"));

	/* Reuse existing commit message in reflog message */
	memset(&pretty_ctx, 0, sizeof(pretty_ctx));
	format_commit_message(partial, "%s", &msg, &pretty_ctx);
	strbuf_trim(&msg);
	strbuf_insert(&msg, 0, "notes: ", 7);
	update_ref(msg.buf, o->local_ref, &oid,
		   is_null_oid(&parent_oid) ? NULL : &parent_oid,
		   0, UPDATE_REFS_DIE_ON_ERR);

	free_notes(t);
	strbuf_release(&msg);
	ret = merge_abort(o);
	free(local_ref_to_free);
	return ret;
}