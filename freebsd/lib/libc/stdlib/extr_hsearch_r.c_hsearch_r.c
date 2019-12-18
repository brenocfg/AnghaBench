#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hsearch_data {struct __hsearch* __hsearch; } ;
struct __hsearch {size_t index_mask; int entries_used; int /*<<< orphan*/  offset_basis; TYPE_1__* entries; } ;
struct TYPE_7__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ ENTRY ;
typedef  scalar_t__ ACTION ;

/* Variables and functions */
 int /*<<< orphan*/  ESRCH ; 
 scalar_t__ FIND ; 
 TYPE_1__* calloc (size_t,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 size_t hsearch_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* hsearch_lookup_free (struct __hsearch*,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
hsearch_r(ENTRY item, ACTION action, ENTRY **retval, struct hsearch_data *htab)
{
	struct __hsearch *hsearch;
	ENTRY *entry, *old_entries, *new_entries;
	size_t hash, index, i, old_hash, old_count, new_count;

	hsearch = htab->__hsearch;
	hash = hsearch_hash(hsearch->offset_basis, item.key);

	/*
	 * Search the hash table for an existing entry for this key.
	 * Stop searching if we run into an unused hash table entry.
	 */
	for (index = hash, i = 0;; index += ++i) {
		entry = &hsearch->entries[index & hsearch->index_mask];
		if (entry->key == NULL)
			break;
		if (strcmp(entry->key, item.key) == 0) {
			*retval = entry;
			return (1);
		}
	}

	/* Only perform the insertion if action is set to ENTER. */
	if (action == FIND) {
		errno = ESRCH;
		return (0);
	}

	if (hsearch->entries_used * 2 >= hsearch->index_mask) {
		/* Preserve the old hash table entries. */
		old_count = hsearch->index_mask + 1;
		old_entries = hsearch->entries;

		/*
		 * Allocate and install a new table if insertion would
		 * yield a hash table that is more than 50% used. By
		 * using 50% as a threshold, a lookup will only take up
		 * to two steps on average.
		 */
		new_count = (hsearch->index_mask + 1) * 2;
		new_entries = calloc(new_count, sizeof(ENTRY));
		if (new_entries == NULL)
			return (0);
		hsearch->entries = new_entries;
		hsearch->index_mask = new_count - 1;

		/* Copy over the entries from the old table to the new table. */
		for (i = 0; i < old_count; ++i) {
			entry = &old_entries[i];
			if (entry->key != NULL) {
				old_hash = hsearch_hash(hsearch->offset_basis,
				    entry->key);
				*hsearch_lookup_free(hsearch, old_hash) =
				    *entry;
			}
		}

		/* Destroy the old hash table entries. */
		free(old_entries);

		/*
		 * Perform a new lookup for a free table entry, so that
		 * we insert the entry into the new hash table.
		 */
		hsearch = htab->__hsearch;
		entry = hsearch_lookup_free(hsearch, hash);
	}

	/* Insert the new entry into the hash table. */
	*entry = item;
	++hsearch->entries_used;
	*retval = entry;
	return (1);
}