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
struct vmci_resource {int /*<<< orphan*/  hash_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_resource*) ; 
 int VMCI_SUCCESS_ENTRY_DEAD ; 
 int /*<<< orphan*/  resource_table ; 
 int vmci_hashtable_release_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_resource_do_remove (struct vmci_resource*) ; 

int
vmci_resource_release(struct vmci_resource *resource)
{
	int result;

	ASSERT(resource);

	result = vmci_hashtable_release_entry(resource_table,
	    &resource->hash_entry);
	if (result == VMCI_SUCCESS_ENTRY_DEAD)
		vmci_resource_do_remove(resource);

	/*
	 * We propagate the information back to caller in case it wants to know
	 * whether entry was freed.
	 */
	return (result);
}