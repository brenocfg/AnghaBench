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
struct vmci_hashtable {struct vmci_hash_entry** entries; int /*<<< orphan*/  size; } ;
struct vmci_handle {int dummy; } ;
struct vmci_hash_entry {struct vmci_hash_entry* next; struct vmci_handle handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_hashtable*) ; 
 scalar_t__ VMCI_HANDLE_TO_CONTEXT_ID (struct vmci_handle) ; 
 scalar_t__ VMCI_HANDLE_TO_RESOURCE_ID (struct vmci_handle) ; 
 int VMCI_HASHTABLE_HASH (struct vmci_handle,int /*<<< orphan*/ ) ; 
 scalar_t__ VMCI_INVALID_ID ; 

__attribute__((used)) static bool
vmci_hashtable_entry_exists_locked(struct vmci_hashtable *table,
    struct vmci_handle handle)

{
	struct vmci_hash_entry *entry;
	int idx;

	ASSERT(table);

	idx = VMCI_HASHTABLE_HASH(handle, table->size);

	entry = table->entries[idx];
	while (entry) {
		if (VMCI_HANDLE_TO_RESOURCE_ID(entry->handle) ==
		    VMCI_HANDLE_TO_RESOURCE_ID(handle))
			if ((VMCI_HANDLE_TO_CONTEXT_ID(entry->handle) ==
			    VMCI_HANDLE_TO_CONTEXT_ID(handle)) ||
			    (VMCI_INVALID_ID == VMCI_HANDLE_TO_CONTEXT_ID(handle)) ||
			    (VMCI_INVALID_ID == VMCI_HANDLE_TO_CONTEXT_ID(entry->handle)))
				return (true);
		entry = entry->next;
	}

	return (false);
}