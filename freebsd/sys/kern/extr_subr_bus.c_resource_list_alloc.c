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
typedef  int u_int ;
struct resource_list_entry {int flags; struct resource* res; scalar_t__ count; scalar_t__ end; scalar_t__ start; } ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
typedef  scalar_t__ rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 struct resource* BUS_ALLOC_RESOURCE (scalar_t__,scalar_t__,int,int*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int RF_ACTIVE ; 
 int RLE_ALLOCATED ; 
 int RLE_RESERVED ; 
 int RMAN_IS_DEFAULT_RANGE (scalar_t__,scalar_t__) ; 
 scalar_t__ bus_activate_resource (scalar_t__,int,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int,int,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 scalar_t__ ulmax (scalar_t__,scalar_t__) ; 

struct resource *
resource_list_alloc(struct resource_list *rl, device_t bus, device_t child,
    int type, int *rid, rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct resource_list_entry *rle = NULL;
	int passthrough = (device_get_parent(child) != bus);
	int isdefault = RMAN_IS_DEFAULT_RANGE(start, end);

	if (passthrough) {
		return (BUS_ALLOC_RESOURCE(device_get_parent(bus), child,
		    type, rid, start, end, count, flags));
	}

	rle = resource_list_find(rl, type, *rid);

	if (!rle)
		return (NULL);		/* no resource of that type/rid */

	if (rle->res) {
		if (rle->flags & RLE_RESERVED) {
			if (rle->flags & RLE_ALLOCATED)
				return (NULL);
			if ((flags & RF_ACTIVE) &&
			    bus_activate_resource(child, type, *rid,
			    rle->res) != 0)
				return (NULL);
			rle->flags |= RLE_ALLOCATED;
			return (rle->res);
		}
		device_printf(bus,
		    "resource entry %#x type %d for child %s is busy\n", *rid,
		    type, device_get_nameunit(child));
		return (NULL);
	}

	if (isdefault) {
		start = rle->start;
		count = ulmax(count, rle->count);
		end = ulmax(rle->end, start + count - 1);
	}

	rle->res = BUS_ALLOC_RESOURCE(device_get_parent(bus), child,
	    type, rid, start, end, count, flags);

	/*
	 * Record the new range.
	 */
	if (rle->res) {
		rle->start = rman_get_start(rle->res);
		rle->end = rman_get_end(rle->res);
		rle->count = count;
	}

	return (rle->res);
}