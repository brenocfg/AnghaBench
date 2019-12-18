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
struct bhnd_resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BHND_BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,struct bhnd_resource*) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ ) ; 

int
bhnd_bus_generic_deactivate_resource(device_t dev, device_t child,
    int type, int rid, struct bhnd_resource *r)
{
	if (device_get_parent(dev) != NULL)
		return (BHND_BUS_DEACTIVATE_RESOURCE(device_get_parent(dev),
		    child, type, rid, r));

	return (EINVAL);
}