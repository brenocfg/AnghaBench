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
struct vmci_hashtable {int size; int /*<<< orphan*/  lock; struct vmci_hashtable* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_hashtable*) ; 
 int /*<<< orphan*/  vmci_cleanup_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_free_kernel_mem (struct vmci_hashtable*,int) ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 

void
vmci_hashtable_destroy(struct vmci_hashtable *table)
{

	ASSERT(table);

	vmci_grab_lock_bh(&table->lock);
	vmci_free_kernel_mem(table->entries, sizeof(*table->entries) *
	    table->size);
	table->entries = NULL;
	vmci_release_lock_bh(&table->lock);
	vmci_cleanup_lock(&table->lock);
	vmci_free_kernel_mem(table, sizeof(*table));
}