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
 int /*<<< orphan*/  resource_table ; 
 int /*<<< orphan*/  vmci_hashtable_hold_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
vmci_resource_hold(struct vmci_resource *resource)
{

	ASSERT(resource);
	vmci_hashtable_hold_entry(resource_table, &resource->hash_entry);
}