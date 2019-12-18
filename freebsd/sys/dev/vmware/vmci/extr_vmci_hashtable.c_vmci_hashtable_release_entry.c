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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_hashtable*) ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int vmci_hashtable_release_entry_locked (struct vmci_hashtable*,struct vmci_hash_entry*) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 

int
vmci_hashtable_release_entry(struct vmci_hashtable *table,
    struct vmci_hash_entry *entry)
{
	int result;

	ASSERT(table);
	vmci_grab_lock_bh(&table->lock);
	result = vmci_hashtable_release_entry_locked(table, entry);
	vmci_release_lock_bh(&table->lock);

	return (result);
}