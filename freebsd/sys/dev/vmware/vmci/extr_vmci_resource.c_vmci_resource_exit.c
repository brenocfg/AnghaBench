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

/* Variables and functions */
 int /*<<< orphan*/  resource_id_lock ; 
 scalar_t__ resource_table ; 
 int /*<<< orphan*/  vmci_cleanup_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_hashtable_destroy (scalar_t__) ; 

void
vmci_resource_exit(void)
{

	/* Cleanup resources.*/
	vmci_cleanup_lock(&resource_id_lock);

	if (resource_table)
		vmci_hashtable_destroy(resource_table);
}