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
struct write_each_note_data {int /*<<< orphan*/  next_non_note; struct tree_write_stack* root; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct tree_write_stack {char* path; TYPE_2__ buf; int /*<<< orphan*/ * next; } ;
struct object_id {int dummy; } ;
struct notes_tree {int /*<<< orphan*/  first_non_note; int /*<<< orphan*/  initialized; } ;
struct TYPE_4__ {int hexsz; } ;

/* Variables and functions */
 int FOR_EACH_NOTE_DONT_UNPACK_SUBTREES ; 
 int FOR_EACH_NOTE_YIELD_SUBTREES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct notes_tree default_notes_tree ; 
 scalar_t__ for_each_note (struct notes_tree*,int,int /*<<< orphan*/ ,struct write_each_note_data*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_2__*) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  tree_type ; 
 scalar_t__ tree_write_stack_finish_subtree (struct tree_write_stack*) ; 
 scalar_t__ write_each_non_note_until (int /*<<< orphan*/ *,struct write_each_note_data*) ; 
 int /*<<< orphan*/  write_each_note ; 
 scalar_t__ write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

int write_notes_tree(struct notes_tree *t, struct object_id *result)
{
	struct tree_write_stack root;
	struct write_each_note_data cb_data;
	int ret;
	int flags;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);

	/* Prepare for traversal of current notes tree */
	root.next = NULL; /* last forward entry in list is grounded */
	strbuf_init(&root.buf, 256 * (32 + the_hash_algo->hexsz)); /* assume 256 entries */
	root.path[0] = root.path[1] = '\0';
	cb_data.root = &root;
	cb_data.next_non_note = t->first_non_note;

	/* Write tree objects representing current notes tree */
	flags = FOR_EACH_NOTE_DONT_UNPACK_SUBTREES |
		FOR_EACH_NOTE_YIELD_SUBTREES;
	ret = for_each_note(t, flags, write_each_note, &cb_data) ||
	      write_each_non_note_until(NULL, &cb_data) ||
	      tree_write_stack_finish_subtree(&root) ||
	      write_object_file(root.buf.buf, root.buf.len, tree_type, result);
	strbuf_release(&root.buf);
	return ret;
}