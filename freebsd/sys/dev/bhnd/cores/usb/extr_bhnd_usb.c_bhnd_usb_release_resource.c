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
struct bhnd_usb_softc {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int BUS_DEACTIVATE_RESOURCE (scalar_t__,scalar_t__,int,int,struct resource*) ; 
 int /*<<< orphan*/  BUS_GET_RESOURCE_LIST (scalar_t__,scalar_t__) ; 
 int RF_ACTIVE ; 
 int SYS_RES_MEMORY ; 
 int bus_generic_rl_release_resource (scalar_t__,scalar_t__,int,int,struct resource*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct bhnd_usb_softc* device_get_softc (scalar_t__) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ ,int,int) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
bhnd_usb_release_resource(device_t dev, device_t child, int type,
    int rid, struct resource *r)
{
	struct bhnd_usb_softc		*sc;
	struct resource_list_entry	*rle;
	bool				 passthrough;
	int				 error;

	sc = device_get_softc(dev);
	passthrough = (device_get_parent(child) != dev);

	/* Delegate to our parent device's bus if the requested resource type
	 * isn't handled locally. */
	if (type != SYS_RES_MEMORY) {
		return (bus_generic_rl_release_resource(dev, child, type, rid,
		    r));
	}

	/* Deactivate resources */
	if (rman_get_flags(r) & RF_ACTIVE) {
		error = BUS_DEACTIVATE_RESOURCE(dev, child, type, rid, r);
		if (error)
			return (error);
	}

	if ((error = rman_release_resource(r)))
		return (error);

	if (!passthrough) {
		/* Clean resource list entry */
		rle = resource_list_find(BUS_GET_RESOURCE_LIST(dev, child),
		    type, rid);
		if (rle != NULL)
			rle->res = NULL;
	}

	return (0);
}