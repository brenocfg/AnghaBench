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
struct resource_list_entry {int /*<<< orphan*/  res; } ;
struct resource {int dummy; } ;
struct pccard_ivar {int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int ENOENT ; 
 struct pccard_ivar* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pccard_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	struct pccard_ivar *dinfo;
	int passthrough = (device_get_parent(child) != dev);
	struct resource_list_entry *rle = NULL;

	if (passthrough)
		return BUS_RELEASE_RESOURCE(device_get_parent(dev), child,
		    type, rid, r);

	dinfo = device_get_ivars(child);

	rle = resource_list_find(&dinfo->resources, type, rid);

	if (!rle) {
		device_printf(dev, "Allocated resource not found, "
		    "%d %#x %#jx %#jx\n",
		    type, rid, rman_get_start(r), rman_get_size(r));
		return ENOENT;
	}
	if (!rle->res) {
		device_printf(dev, "Allocated resource not recorded\n");
		return ENOENT;
	}
	/*
	 * Deactivate the resource (since it is being released), and
	 * assign it to the bus.
	 */
	BUS_DEACTIVATE_RESOURCE(dev, child, type, rid, rle->res);
	rman_set_device(rle->res, dev);
	return (0);
}