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
typedef  int /*<<< orphan*/  u_int ;
struct bcma_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 struct bcma_devinfo* bcma_alloc_dinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct bcma_devinfo*) ; 

__attribute__((used)) static device_t
bcma_add_child(device_t dev, u_int order, const char *name, int unit)
{
	struct bcma_devinfo	*dinfo;
	device_t		 child;

	child = device_add_child_ordered(dev, order, name, unit);
	if (child == NULL)
		return (NULL);

	if ((dinfo = bcma_alloc_dinfo(dev)) == NULL) {
		device_delete_child(dev, child);
		return (NULL);
	}

	device_set_ivars(child, dinfo);

	return (child);
}