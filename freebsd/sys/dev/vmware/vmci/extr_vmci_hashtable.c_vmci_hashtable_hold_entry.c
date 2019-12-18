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
struct vmci_hashtable {int /*<<< orphan*/  lock; int /*<<< orphan*/  ref_count; } ;
struct vmci_hash_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_hashtable*) ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 

void
vmci_hashtable_hold_entry(struct vmci_hashtable *table,
    struct vmci_hash_entry *entry)
{

	ASSERT(table);
	ASSERT(entry);

	vmci_grab_lock_bh(&table->lock);
	entry->ref_count++;
	vmci_release_lock_bh(&table->lock);
}