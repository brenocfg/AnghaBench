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
struct vmci_hashtable {int /*<<< orphan*/  lock; } ;
struct vmci_hash_entry {int dummy; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_hashtable*) ; 
 scalar_t__ VMCI_HANDLE_EQUAL (struct vmci_handle,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 struct vmci_hash_entry* vmci_hashtable_get_entry_locked (struct vmci_hashtable*,struct vmci_handle) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 

struct vmci_hash_entry *
vmci_hashtable_get_entry(struct vmci_hashtable *table,
    struct vmci_handle handle)
{
	struct vmci_hash_entry *entry;

	if (VMCI_HANDLE_EQUAL(handle, VMCI_INVALID_HANDLE))
		return (NULL);

	ASSERT(table);

	vmci_grab_lock_bh(&table->lock);
	entry = vmci_hashtable_get_entry_locked(table, handle);
	vmci_release_lock_bh(&table->lock);

	return (entry);
}