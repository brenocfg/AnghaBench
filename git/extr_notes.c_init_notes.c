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
struct notes_tree {int initialized; struct int_node* root; scalar_t__ dirty; scalar_t__ combine_notes; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * update_ref; int /*<<< orphan*/ * prev_non_note; int /*<<< orphan*/ * first_non_note; } ;
struct leaf_node {int /*<<< orphan*/  val_oid; int /*<<< orphan*/  key_oid; } ;
struct int_node {int dummy; } ;
typedef  scalar_t__ combine_notes_fn ;

/* Variables and functions */
 int NOTES_INIT_EMPTY ; 
 int NOTES_INIT_WRITABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ combine_notes_concatenate ; 
 char* default_notes_ref () ; 
 struct notes_tree default_notes_tree ; 
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 scalar_t__ get_oid_treeish (char const*,struct object_id*) ; 
 scalar_t__ get_tree_entry (int /*<<< orphan*/ ,struct object_id*,char*,struct object_id*,unsigned short*) ; 
 int /*<<< orphan*/  load_subtree (struct notes_tree*,struct leaf_node*,struct int_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ read_ref (char const*,struct object_id*) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ xcalloc (int,int) ; 
 int /*<<< orphan*/ * xstrdup_or_null (char const*) ; 

void init_notes(struct notes_tree *t, const char *notes_ref,
		combine_notes_fn combine_notes, int flags)
{
	struct object_id oid, object_oid;
	unsigned short mode;
	struct leaf_node root_tree;

	if (!t)
		t = &default_notes_tree;
	assert(!t->initialized);

	if (!notes_ref)
		notes_ref = default_notes_ref();

	if (!combine_notes)
		combine_notes = combine_notes_concatenate;

	t->root = (struct int_node *) xcalloc(1, sizeof(struct int_node));
	t->first_non_note = NULL;
	t->prev_non_note = NULL;
	t->ref = xstrdup_or_null(notes_ref);
	t->update_ref = (flags & NOTES_INIT_WRITABLE) ? t->ref : NULL;
	t->combine_notes = combine_notes;
	t->initialized = 1;
	t->dirty = 0;

	if (flags & NOTES_INIT_EMPTY || !notes_ref ||
	    get_oid_treeish(notes_ref, &object_oid))
		return;
	if (flags & NOTES_INIT_WRITABLE && read_ref(notes_ref, &object_oid))
		die("Cannot use notes ref %s", notes_ref);
	if (get_tree_entry(the_repository, &object_oid, "", &oid, &mode))
		die("Failed to read notes tree referenced by %s (%s)",
		    notes_ref, oid_to_hex(&object_oid));

	oidclr(&root_tree.key_oid);
	oidcpy(&root_tree.val_oid, &oid);
	load_subtree(t, &root_tree, t->root, 0);
}