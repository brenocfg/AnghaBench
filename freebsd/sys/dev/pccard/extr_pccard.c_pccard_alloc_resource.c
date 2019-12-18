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
struct resource_list_entry {struct resource* res; } ;
struct resource {int dummy; } ;
struct pccard_ivar {int /*<<< orphan*/  resources; } ;
typedef  int rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ACTIVATE_RESOURCE (scalar_t__,scalar_t__,int,int,struct resource*) ; 
 struct resource* BUS_ALLOC_RESOURCE (scalar_t__,scalar_t__,int,int*,int,int,int,int) ; 
 int RF_ACTIVE ; 
 scalar_t__ RMAN_IS_DEFAULT_RANGE (int,int) ; 
 struct resource* bus_alloc_resource (scalar_t__,int,int*,int,int,int,int) ; 
 struct pccard_ivar* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ rman_get_device (struct resource*) ; 
 int /*<<< orphan*/  rman_get_end (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_device (struct resource*,scalar_t__) ; 

__attribute__((used)) static struct resource *
pccard_alloc_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct pccard_ivar *dinfo;
	struct resource_list_entry *rle = NULL;
	int passthrough = (device_get_parent(child) != dev);
	int isdefault = (RMAN_IS_DEFAULT_RANGE(start, end) && count == 1);
	struct resource *r = NULL;

	/* XXX I'm no longer sure this is right */
	if (passthrough) {
		return (BUS_ALLOC_RESOURCE(device_get_parent(dev), child,
		    type, rid, start, end, count, flags));
	}

	dinfo = device_get_ivars(child);
	rle = resource_list_find(&dinfo->resources, type, *rid);

	if (rle == NULL && isdefault)
		return (NULL);	/* no resource of that type/rid */
	if (rle == NULL || rle->res == NULL) {
		/* XXX Need to adjust flags */
		r = bus_alloc_resource(dev, type, rid, start, end,
		  count, flags);
		if (r == NULL)
		    goto bad;
		resource_list_add(&dinfo->resources, type, *rid,
		  rman_get_start(r), rman_get_end(r), count);
		rle = resource_list_find(&dinfo->resources, type, *rid);
		if (!rle)
		    goto bad;
		rle->res = r;
	}
	/*
	 * If dev doesn't own the device, then we can't give this device
	 * out.
	 */
	if (rman_get_device(rle->res) != dev)
		return (NULL);
	rman_set_device(rle->res, child);
	if (flags & RF_ACTIVE)
		BUS_ACTIVATE_RESOURCE(dev, child, type, *rid, rle->res);
	return (rle->res);
bad:;
	device_printf(dev, "WARNING: Resource not reserved by pccard\n");
	return (NULL);
}