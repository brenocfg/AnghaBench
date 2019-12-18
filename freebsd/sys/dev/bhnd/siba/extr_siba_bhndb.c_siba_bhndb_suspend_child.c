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
struct siba_devinfo {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SUSPEND_CHILD (scalar_t__,scalar_t__) ; 
 int bhnd_generic_br_suspend_child (scalar_t__,scalar_t__) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  siba_bhndb_suspend_cfgblocks (scalar_t__,struct siba_devinfo*) ; 

__attribute__((used)) static int
siba_bhndb_suspend_child(device_t dev, device_t child)
{
	struct siba_devinfo	*dinfo;
	int			 error;

	if (device_get_parent(child) != dev)
		BUS_SUSPEND_CHILD(device_get_parent(dev), child);

	dinfo = device_get_ivars(child);

	/* Suspend the child */
	if ((error = bhnd_generic_br_suspend_child(dev, child)))
		return (error);

	/* Suspend resource references to the child's config registers */
	siba_bhndb_suspend_cfgblocks(dev, dinfo);
	
	return (0);
}