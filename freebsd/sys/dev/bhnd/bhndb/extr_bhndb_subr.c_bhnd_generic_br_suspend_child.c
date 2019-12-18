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
struct resource_list {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BUS_SUSPEND_CHILD (scalar_t__,scalar_t__) ; 
 int EBUSY ; 
 int bhnd_generic_suspend_child (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bhndb_do_suspend_resources (scalar_t__,struct resource_list*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 scalar_t__ device_is_suspended (scalar_t__) ; 

int
bhnd_generic_br_suspend_child(device_t dev, device_t child)
{
	struct resource_list		*rl;
	int				 error;

	if (device_get_parent(child) != dev)
		BUS_SUSPEND_CHILD(device_get_parent(dev), child);

	if (device_is_suspended(child))
		return (EBUSY);

	/* Suspend the child device */
	if ((error = bhnd_generic_suspend_child(dev, child)))
		return (error);

	/* Fetch the resource list. If none, there's nothing else to do */
	rl = BUS_GET_RESOURCE_LIST(device_get_parent(child), child);
	if (rl == NULL)
		return (0);

	/* Suspend all child resources. */
	bhndb_do_suspend_resources(dev, rl);

	return (0);
}