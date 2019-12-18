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
struct notes_tree {int /*<<< orphan*/  initialized; } ;
struct note_delete_list {struct note_delete_list* next; int /*<<< orphan*/  sha1; } ;

/* Variables and functions */
 int NOTES_PRUNE_DRYRUN ; 
 int NOTES_PRUNE_VERBOSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct notes_tree default_notes_tree ; 
 int /*<<< orphan*/  for_each_note (struct notes_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct note_delete_list**) ; 
 char* hash_to_hex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  prune_notes_helper ; 
 int /*<<< orphan*/  remove_note (struct notes_tree*,int /*<<< orphan*/ ) ; 

void prune_notes(struct notes_tree *t, int flags)
{
	struct note_delete_list *l = NULL;

	if (!t)
		t = &default_notes_tree;
	assert(t->initialized);

	for_each_note(t, 0, prune_notes_helper, &l);

	while (l) {
		if (flags & NOTES_PRUNE_VERBOSE)
			printf("%s\n", hash_to_hex(l->sha1));
		if (!(flags & NOTES_PRUNE_DRYRUN))
			remove_note(t, l->sha1);
		l = l->next;
	}
}