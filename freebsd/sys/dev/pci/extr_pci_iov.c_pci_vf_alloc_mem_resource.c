#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct resource_list_entry {struct resource* res; } ;
struct resource {int dummy; } ;
struct pcicfg_iov {int /*<<< orphan*/  rman; } ;
struct pci_map {int pm_size; scalar_t__ pm_value; } ;
struct TYPE_2__ {struct pcicfg_iov* iov; } ;
struct pci_devinfo {int /*<<< orphan*/  resources; TYPE_1__ cfg; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int pci_addr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct pci_map* pci_find_bar (int /*<<< orphan*/ ,int) ; 
 struct resource_list_entry* resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  resource_list_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

struct resource *
pci_vf_alloc_mem_resource(device_t dev, device_t child, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct pci_devinfo *dinfo;
	struct pcicfg_iov *iov;
	struct pci_map *map;
	struct resource *res;
	struct resource_list_entry *rle;
	rman_res_t bar_start, bar_end;
	pci_addr_t bar_length;
	int error;

	dinfo = device_get_ivars(child);
	iov = dinfo->cfg.iov;

	map = pci_find_bar(child, *rid);
	if (map == NULL)
		return (NULL);

	bar_length = 1 << map->pm_size;
	bar_start = map->pm_value;
	bar_end = bar_start + bar_length - 1;

	/* Make sure that the resource fits the constraints. */
	if (bar_start >= end || bar_end <= bar_start || count != 1)
		return (NULL);

	/* Clamp the resource to the constraints if necessary. */
	if (bar_start < start)
		bar_start = start;
	if (bar_end > end)
		bar_end = end;
	bar_length = bar_end - bar_start + 1;

	res = rman_reserve_resource(&iov->rman, bar_start, bar_end,
	    bar_length, flags, child);
	if (res == NULL)
		return (NULL);

	rle = resource_list_add(&dinfo->resources, SYS_RES_MEMORY, *rid,
	    bar_start, bar_end, 1);
	if (rle == NULL) {
		rman_release_resource(res);
		return (NULL);
	}

	rman_set_rid(res, *rid);

	if (flags & RF_ACTIVE) {
		error = bus_activate_resource(child, SYS_RES_MEMORY, *rid, res);
		if (error != 0) {
			resource_list_delete(&dinfo->resources, SYS_RES_MEMORY,
			    *rid);
			rman_release_resource(res);
			return (NULL);
		}
	}
	rle->res = res;

	return (res);
}