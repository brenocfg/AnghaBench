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
struct rman {int dummy; } ;
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct resource {int dummy; } ;
struct chipc_softc {int dummy; } ;
struct chipc_region {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/  RF_ALLOCATED ; 
 int bus_generic_rl_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct chipc_region* chipc_find_region (struct chipc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rman* chipc_get_rman (struct chipc_softc*,int) ; 
 int /*<<< orphan*/  chipc_release_region (struct chipc_softc*,struct chipc_region*,int /*<<< orphan*/ ) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rman_get_end (struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
chipc_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	struct chipc_softc		*sc;
	struct chipc_region		*cr;
	struct rman			*rm;
	struct resource_list_entry	*rle;
	int			 	 error;

	sc = device_get_softc(dev);

	/* Handled by parent bus? */
	rm = chipc_get_rman(sc, type);
	if (rm == NULL || !rman_is_region_manager(r, rm)) {
		return (bus_generic_rl_release_resource(dev, child, type, rid,
		    r));
	}

	/* Locate the mapping region */
	cr = chipc_find_region(sc, rman_get_start(r), rman_get_end(r));
	if (cr == NULL)
		return (EINVAL);

	/* Deactivate resources */
	if (rman_get_flags(r) & RF_ACTIVE) {
		error = BUS_DEACTIVATE_RESOURCE(dev, child, type, rid, r);
		if (error)
			return (error);
	}

	if ((error = rman_release_resource(r)))
		return (error);

	/* Drop allocation reference */
	chipc_release_region(sc, cr, RF_ALLOCATED);

	/* Clear reference from the resource list entry if exists */
	rle = resource_list_find(BUS_GET_RESOURCE_LIST(dev, child), type, rid);
	if (rle != NULL)
		rle->res = NULL;

	return (0);
}