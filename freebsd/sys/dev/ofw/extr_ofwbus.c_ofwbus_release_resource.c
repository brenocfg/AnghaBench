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
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct resource {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_GET_RESOURCE_LIST (scalar_t__,scalar_t__) ; 
 int RF_ACTIVE ; 
 int bus_deactivate_resource (scalar_t__,int,int,struct resource*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ ,int,int) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
ofwbus_release_resource(device_t bus, device_t child, int type,
    int rid, struct resource *r)
{
	struct resource_list_entry *rle;
	int passthrough;
	int error;

	passthrough = (device_get_parent(child) != bus);
	if (!passthrough) {
		/* Clean resource list entry */
		rle = resource_list_find(BUS_GET_RESOURCE_LIST(bus, child),
		    type, rid);
		if (rle != NULL)
			rle->res = NULL;
	}

	if ((rman_get_flags(r) & RF_ACTIVE) != 0) {
		error = bus_deactivate_resource(child, type, rid, r);
		if (error)
			return (error);
	}
	return (rman_release_resource(r));
}