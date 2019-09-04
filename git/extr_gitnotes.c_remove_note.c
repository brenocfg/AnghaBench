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
struct notes_tree {int dirty; int /*<<< orphan*/  root; int /*<<< orphan*/  initialized; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct leaf_node {int /*<<< orphan*/  val_oid; TYPE_1__ key_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct notes_tree default_notes_tree ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  note_tree_remove (struct notes_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct leaf_node*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 

int remove_note(struct notes_tree *t, const unsigned char *object_sha1)
{
	struct leaf_node l;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	hashcpy(l.key_oid.hash, object_sha1);
	oidclr(&l.val_oid);
	note_tree_remove(t, t->root, 0, &l);
	if (is_null_oid(&l.val_oid)) /* no note was removed */
		return 1;
	t->dirty = 1;
	return 0;
}