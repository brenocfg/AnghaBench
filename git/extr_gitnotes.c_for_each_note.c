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
struct notes_tree {int /*<<< orphan*/  root; int /*<<< orphan*/  initialized; } ;
typedef  int /*<<< orphan*/  each_note_fn ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct notes_tree default_notes_tree ; 
 int for_each_note_helper (struct notes_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

int for_each_note(struct notes_tree *t, int flags, each_note_fn fn,
		void *cb_data)
{
	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);
	return for_each_note_helper(t, t->root, 0, 0, flags, fn, cb_data);
}