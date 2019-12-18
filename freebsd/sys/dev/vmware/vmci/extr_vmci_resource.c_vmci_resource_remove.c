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
typedef  int /*<<< orphan*/  vmci_resource_type ;
struct vmci_resource {int /*<<< orphan*/  hash_entry; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  resource_table ; 
 int /*<<< orphan*/  vmci_hashtable_remove_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vmci_resource* vmci_resource_get (struct vmci_handle,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_resource_release (struct vmci_resource*) ; 

void
vmci_resource_remove(struct vmci_handle resource_handle,
    vmci_resource_type resource_type)
{
	struct vmci_resource *resource;

	resource = vmci_resource_get(resource_handle, resource_type);
	if (resource == NULL)
		return;

	/* Remove resource from hashtable. */
	vmci_hashtable_remove_entry(resource_table, &resource->hash_entry);

	vmci_resource_release(resource);
	/* resource could be freed by now. */
}