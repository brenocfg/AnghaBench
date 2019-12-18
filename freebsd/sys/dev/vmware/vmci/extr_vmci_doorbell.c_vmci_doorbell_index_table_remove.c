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
struct vmci_doorbell_entry {int idx; int /*<<< orphan*/  resource; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_doorbell_entry*) ; 
 int /*<<< orphan*/  idx_list_item ; 
 int last_notify_idx_released ; 
 int max_notify_idx ; 
 int /*<<< orphan*/  notify_idx_count ; 
 int /*<<< orphan*/  vmci_doorbell_index_table_find (int) ; 
 TYPE_1__ vmci_doorbell_it ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_list_remove (struct vmci_doorbell_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_resource_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmci_doorbell_index_table_remove(struct vmci_doorbell_entry *entry)
{
	ASSERT(entry);

	vmci_grab_lock_bh(&vmci_doorbell_it.lock);

	vmci_list_remove(entry, idx_list_item);

	notify_idx_count--;
	if (entry->idx == max_notify_idx - 1) {
		/*
		 * If we delete an entry with the maximum known notification
		 * index, we take the opportunity to prune the current max. As
		 * there might be other unused indices immediately below, we
		 * lower the maximum until we hit an index in use
		 */

		while (max_notify_idx > 0 &&
		    !vmci_doorbell_index_table_find(max_notify_idx - 1))
			max_notify_idx--;
	}
	last_notify_idx_released = entry->idx;

	vmci_release_lock_bh(&vmci_doorbell_it.lock);

	vmci_resource_release(&entry->resource);
}