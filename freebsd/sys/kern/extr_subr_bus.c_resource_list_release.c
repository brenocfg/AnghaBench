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
struct resource_list_entry {int flags; int /*<<< orphan*/ * res; } ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int BUS_RELEASE_RESOURCE (scalar_t__,scalar_t__,int,int,struct resource*) ; 
 int EINVAL ; 
 int RF_ACTIVE ; 
 int RLE_ALLOCATED ; 
 int RLE_RESERVED ; 
 int bus_deactivate_resource (scalar_t__,int,int,struct resource*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 
 int rman_get_flags (struct resource*) ; 

int
resource_list_release(struct resource_list *rl, device_t bus, device_t child,
    int type, int rid, struct resource *res)
{
	struct resource_list_entry *rle = NULL;
	int passthrough = (device_get_parent(child) != bus);
	int error;

	if (passthrough) {
		return (BUS_RELEASE_RESOURCE(device_get_parent(bus), child,
		    type, rid, res));
	}

	rle = resource_list_find(rl, type, rid);

	if (!rle)
		panic("resource_list_release: can't find resource");
	if (!rle->res)
		panic("resource_list_release: resource entry is not busy");
	if (rle->flags & RLE_RESERVED) {
		if (rle->flags & RLE_ALLOCATED) {
			if (rman_get_flags(res) & RF_ACTIVE) {
				error = bus_deactivate_resource(child, type,
				    rid, res);
				if (error)
					return (error);
			}
			rle->flags &= ~RLE_ALLOCATED;
			return (0);
		}
		return (EINVAL);
	}

	error = BUS_RELEASE_RESOURCE(device_get_parent(bus), child,
	    type, rid, res);
	if (error)
		return (error);

	rle->res = NULL;
	return (0);
}