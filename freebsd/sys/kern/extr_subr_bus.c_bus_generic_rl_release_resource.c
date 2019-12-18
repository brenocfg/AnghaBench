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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int resource_list_release (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 

int
bus_generic_rl_release_resource(device_t dev, device_t child, int type,
    int rid, struct resource *r)
{
	struct resource_list *		rl = NULL;

	if (device_get_parent(child) != dev)
		return (BUS_RELEASE_RESOURCE(device_get_parent(dev), child,
		    type, rid, r));

	rl = BUS_GET_RESOURCE_LIST(dev, child);
	if (!rl)
		return (EINVAL);

	return (resource_list_release(rl, dev, child, type, rid, r));
}