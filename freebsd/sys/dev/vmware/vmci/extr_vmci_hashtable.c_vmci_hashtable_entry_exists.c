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
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_hashtable*) ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int vmci_hashtable_entry_exists_locked (struct vmci_hashtable*,struct vmci_handle) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 

bool
vmci_hashtable_entry_exists(struct vmci_hashtable *table,
    struct vmci_handle handle)
{
	bool exists;

	ASSERT(table);

	vmci_grab_lock_bh(&table->lock);
	exists = vmci_hashtable_entry_exists_locked(table, handle);
	vmci_release_lock_bh(&table->lock);

	return (exists);
}