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
struct vmci_hashtable {int size; struct vmci_hashtable* entries; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_MEMORY_NORMAL ; 
 scalar_t__ VMCI_SUCCESS ; 
 int /*<<< orphan*/  memset (struct vmci_hashtable*,int /*<<< orphan*/ ,int) ; 
 void* vmci_alloc_kernel_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_free_kernel_mem (struct vmci_hashtable*,int) ; 
 scalar_t__ vmci_init_lock (int /*<<< orphan*/ *,char*) ; 

struct vmci_hashtable *
vmci_hashtable_create(int size)
{
	struct vmci_hashtable *table;

	table = vmci_alloc_kernel_mem(sizeof(*table),
	    VMCI_MEMORY_NORMAL);
	if (table == NULL)
		return (NULL);
	memset(table, 0, sizeof(*table));

	table->entries = vmci_alloc_kernel_mem(sizeof(*table->entries) * size,
	    VMCI_MEMORY_NORMAL);
	if (table->entries == NULL) {
		vmci_free_kernel_mem(table, sizeof(*table));
		return (NULL);
	}
	memset(table->entries, 0, sizeof(*table->entries) * size);
	table->size = size;
	if (vmci_init_lock(&table->lock, "VMCI Hashtable lock") <
	    VMCI_SUCCESS) {
		vmci_free_kernel_mem(table->entries, sizeof(*table->entries) * size);
		vmci_free_kernel_mem(table, sizeof(*table));
		return (NULL);
	}

	return (table);
}