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
struct bcma_devinfo {TYPE_1__* res_agent; } ;
typedef  scalar_t__ device_t ;
struct TYPE_2__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_SUSPEND_RESOURCE (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SUSPEND_CHILD (scalar_t__,scalar_t__) ; 
 int EBUSY ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_generic_br_suspend_child (scalar_t__,scalar_t__) ; 
 struct bcma_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 scalar_t__ device_is_suspended (scalar_t__) ; 

__attribute__((used)) static int
bcma_bhndb_suspend_child(device_t dev, device_t child)
{
	struct bcma_devinfo	*dinfo;
	int			 error;

	if (device_get_parent(child) != dev)
		BUS_SUSPEND_CHILD(device_get_parent(dev), child);
	
	if (device_is_suspended(child))
		return (EBUSY);

	dinfo = device_get_ivars(child);

	/* Suspend the child */
	if ((error = bhnd_generic_br_suspend_child(dev, child)))
		return (error);

	/* Suspend child's agent resource  */
	if (dinfo->res_agent != NULL)
		BHNDB_SUSPEND_RESOURCE(device_get_parent(dev), dev,
		    SYS_RES_MEMORY, dinfo->res_agent->res);
	
	return (0);
}