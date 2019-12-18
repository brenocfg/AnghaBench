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
struct vmci_hashtable {scalar_t__ ref_count; } ;
struct vmci_hash_entry {scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_hashtable*) ; 
 int VMCI_SUCCESS ; 
 int VMCI_SUCCESS_ENTRY_DEAD ; 
 int /*<<< orphan*/  hashtable_unlink_entry (struct vmci_hashtable*,struct vmci_hashtable*) ; 

__attribute__((used)) static int
vmci_hashtable_release_entry_locked(struct vmci_hashtable *table,
    struct vmci_hash_entry *entry)
{
	int result = VMCI_SUCCESS;

	ASSERT(table);
	ASSERT(entry);

	entry->ref_count--;
	/* Check if this is last reference and report if so. */
	if (entry->ref_count == 0) {

		/*
		 * Remove entry from hash table if not already removed. This
		 * could have happened already because VMCIHashTable_RemoveEntry
		 * was called to unlink it. We ignore if it is not found.
		 * Datagram handles will often have RemoveEntry called, whereas
		 * SharedMemory regions rely on ReleaseEntry to unlink the entry
		 * , since the creator does not call RemoveEntry when it
		 * detaches.
		 */

		hashtable_unlink_entry(table, entry);
		result = VMCI_SUCCESS_ENTRY_DEAD;
	}

	return (result);
}