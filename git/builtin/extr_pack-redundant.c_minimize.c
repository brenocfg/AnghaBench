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
struct pack_list {struct pack_list* next; struct llist* remaining_objects; TYPE_1__* unique_objects; } ;
struct llist {scalar_t__ size; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_objects ; 
 int /*<<< orphan*/  free (struct llist*) ; 
 struct llist* llist_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llist_sorted_difference_inplace (struct llist*,struct llist*) ; 
 struct pack_list* local_packs ; 
 int /*<<< orphan*/  pack_list_insert (struct pack_list**,struct pack_list*) ; 
 int /*<<< orphan*/  sort_pack_list (struct pack_list**) ; 

__attribute__((used)) static void minimize(struct pack_list **min)
{
	struct pack_list *pl, *unique = NULL, *non_unique = NULL;
	struct llist *missing, *unique_pack_objects;

	pl = local_packs;
	while (pl) {
		if (pl->unique_objects->size)
			pack_list_insert(&unique, pl);
		else
			pack_list_insert(&non_unique, pl);
		pl = pl->next;
	}
	/* find out which objects are missing from the set of unique packs */
	missing = llist_copy(all_objects);
	pl = unique;
	while (pl) {
		llist_sorted_difference_inplace(missing, pl->remaining_objects);
		pl = pl->next;
	}

	*min = unique;

	/* return if there are no objects missing from the unique set */
	if (missing->size == 0) {
		free(missing);
		return;
	}

	unique_pack_objects = llist_copy(all_objects);
	llist_sorted_difference_inplace(unique_pack_objects, missing);

	/* remove unique pack objects from the non_unique packs */
	pl = non_unique;
	while (pl) {
		llist_sorted_difference_inplace(pl->remaining_objects, unique_pack_objects);
		pl = pl->next;
	}

	while (non_unique) {
		/* sort the non_unique packs, greater size of remaining_objects first */
		sort_pack_list(&non_unique);
		if (non_unique->remaining_objects->size == 0)
			break;

		pack_list_insert(min, non_unique);

		for (pl = non_unique->next; pl && pl->remaining_objects->size > 0;  pl = pl->next)
			llist_sorted_difference_inplace(pl->remaining_objects, non_unique->remaining_objects);

		non_unique = non_unique->next;
	}
}