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
struct pci_devinfo {int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_deactivate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

int
pci_vf_release_mem_resource(device_t dev, device_t child, int rid,
    struct resource *r)
{
	struct pci_devinfo *dinfo;
	struct resource_list_entry *rle;
	int error;

	dinfo = device_get_ivars(child);

	if (rman_get_flags(r) & RF_ACTIVE) {
		error = bus_deactivate_resource(child, SYS_RES_MEMORY, rid, r);
		if (error != 0)
			return (error);
	}

	rle = resource_list_find(&dinfo->resources, SYS_RES_MEMORY, rid);
	if (rle != NULL) {
		rle->res = NULL;
		resource_list_delete(&dinfo->resources, SYS_RES_MEMORY,
		    rid);
	}

	return (rman_release_resource(r));
}