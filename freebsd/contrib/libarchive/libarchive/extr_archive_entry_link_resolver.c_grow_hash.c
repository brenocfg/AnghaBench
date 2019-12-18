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
struct links_entry {size_t hash; struct links_entry* previous; struct links_entry* next; } ;
struct archive_entry_linkresolver {int number_buckets; struct links_entry** buckets; } ;

/* Variables and functions */
 struct links_entry** calloc (size_t,int) ; 
 int /*<<< orphan*/  free (struct links_entry**) ; 

__attribute__((used)) static void
grow_hash(struct archive_entry_linkresolver *res)
{
	struct links_entry *le, **new_buckets;
	size_t new_size;
	size_t i, bucket;

	/* Try to enlarge the bucket list. */
	new_size = res->number_buckets * 2;
	if (new_size < res->number_buckets)
		return;
	new_buckets = calloc(new_size, sizeof(struct links_entry *));

	if (new_buckets == NULL)
		return;

	for (i = 0; i < res->number_buckets; i++) {
		while (res->buckets[i] != NULL) {
			/* Remove entry from old bucket. */
			le = res->buckets[i];
			res->buckets[i] = le->next;

			/* Add entry to new bucket. */
			bucket = le->hash & (new_size - 1);

			if (new_buckets[bucket] != NULL)
				new_buckets[bucket]->previous = le;
			le->next = new_buckets[bucket];
			le->previous = NULL;
			new_buckets[bucket] = le;
		}
	}
	free(res->buckets);
	res->buckets = new_buckets;
	res->number_buckets = new_size;
}