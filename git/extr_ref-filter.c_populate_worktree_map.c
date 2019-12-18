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
struct worktree {scalar_t__ head_ref; } ;
struct ref_to_worktree_entry {int /*<<< orphan*/  ent; struct worktree* wt; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_add (struct hashmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strhash (scalar_t__) ; 
 struct ref_to_worktree_entry* xmalloc (int) ; 

__attribute__((used)) static void populate_worktree_map(struct hashmap *map, struct worktree **worktrees)
{
	int i;

	for (i = 0; worktrees[i]; i++) {
		if (worktrees[i]->head_ref) {
			struct ref_to_worktree_entry *entry;
			entry = xmalloc(sizeof(*entry));
			entry->wt = worktrees[i];
			hashmap_entry_init(&entry->ent,
					strhash(worktrees[i]->head_ref));

			hashmap_add(map, &entry->ent);
		}
	}
}