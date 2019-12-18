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
struct links_entry {struct links_entry* next; TYPE_1__* previous; int /*<<< orphan*/ * entry; int /*<<< orphan*/ * canonical; } ;
struct archive_entry_linkresolver {size_t number_buckets; struct links_entry* spare; int /*<<< orphan*/  number_entries; struct links_entry** buckets; } ;
struct TYPE_2__ {struct links_entry* next; } ;

/* Variables and functions */
 int NEXT_ENTRY_DEFERRED ; 
 int NEXT_ENTRY_PARTIAL ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct links_entry*) ; 

__attribute__((used)) static struct links_entry *
next_entry(struct archive_entry_linkresolver *res, int mode)
{
	struct links_entry	*le;
	size_t			 bucket;

	/* Free a held entry. */
	if (res->spare != NULL) {
		archive_entry_free(res->spare->canonical);
		archive_entry_free(res->spare->entry);
		free(res->spare);
		res->spare = NULL;
	}

	/* Look for next non-empty bucket in the links cache. */
	for (bucket = 0; bucket < res->number_buckets; bucket++) {
		for (le = res->buckets[bucket]; le != NULL; le = le->next) {
			if (le->entry != NULL &&
			    (mode & NEXT_ENTRY_DEFERRED) == 0)
				continue;
			if (le->entry == NULL &&
			    (mode & NEXT_ENTRY_PARTIAL) == 0)
				continue;
			/* Remove it from this hash bucket. */
			if (le->next != NULL)
				le->next->previous = le->previous;
			if (le->previous != NULL)
				le->previous->next = le->next;
			else
				res->buckets[bucket] = le->next;
			res->number_entries--;
			/* Defer freeing this entry. */
			res->spare = le;
			return (le);
		}
	}
	return (NULL);
}