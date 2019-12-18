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
struct rman {int dummy; } ;
struct resource_list_entry {int start; int end; int count; } ;
struct resource {int dummy; } ;
struct nexus_device {int /*<<< orphan*/  nx_resources; } ;
typedef  int rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 struct nexus_device* DEVTONX (scalar_t__) ; 
 int RF_ACTIVE ; 
 scalar_t__ RMAN_IS_DEFAULT_RANGE (int,int) ; 
 scalar_t__ bus_activate_resource (scalar_t__,int,int,struct resource*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct rman* nexus_rman (int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,int,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

__attribute__((used)) static struct resource *
nexus_alloc_resource(device_t bus, device_t child, int type, int *rid,
		     rman_res_t start, rman_res_t end, rman_res_t count,
		     u_int flags)
{
	struct nexus_device *ndev = DEVTONX(child);
	struct	resource *rv;
	struct resource_list_entry *rle;
	struct	rman *rm;
	int needactivate = flags & RF_ACTIVE;

	/*
	 * If this is an allocation of the "default" range for a given
	 * RID, and we know what the resources for this device are
	 * (ie. they aren't maintained by a child bus), then work out
	 * the start/end values.
	 */
	if (RMAN_IS_DEFAULT_RANGE(start, end) && (count == 1)) {
		if (device_get_parent(child) != bus || ndev == NULL)
			return(NULL);
		rle = resource_list_find(&ndev->nx_resources, type, *rid);
		if (rle == NULL)
			return(NULL);
		start = rle->start;
		end = rle->end;
		count = rle->count;
	}

	flags &= ~RF_ACTIVE;
	rm = nexus_rman(type);
	if (rm == NULL)
		return (NULL);

	rv = rman_reserve_resource(rm, start, end, count, flags, child);
	if (rv == NULL)
		return 0;
	rman_set_rid(rv, *rid);

	if (needactivate) {
		if (bus_activate_resource(child, type, *rid, rv)) {
			rman_release_resource(rv);
			return 0;
		}
	}

	return rv;
}