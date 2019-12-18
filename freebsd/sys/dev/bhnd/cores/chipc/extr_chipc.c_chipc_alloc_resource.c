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
struct resource_list_entry {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  count; struct resource* res; } ;
struct resource {int dummy; } ;
struct chipc_softc {struct chipc_region* core_region; } ;
struct chipc_region {scalar_t__ cr_addr; scalar_t__ cr_end; scalar_t__ cr_count; } ;
typedef  scalar_t__ rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_GET_RESOURCE_LIST (scalar_t__,scalar_t__) ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/  RF_ALLOCATED ; 
 int RMAN_IS_DEFAULT_RANGE (scalar_t__,scalar_t__) ; 
 int bus_activate_resource (scalar_t__,int,int,struct resource*) ; 
 struct resource* bus_generic_rl_alloc_resource (scalar_t__,scalar_t__,int,int*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 struct chipc_region* chipc_find_region (struct chipc_softc*,scalar_t__,scalar_t__) ; 
 struct rman* chipc_get_rman (struct chipc_softc*,int) ; 
 int /*<<< orphan*/  chipc_release_region (struct chipc_softc*,struct chipc_region*,int /*<<< orphan*/ ) ; 
 int chipc_retain_region (struct chipc_softc*,struct chipc_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct chipc_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int,int,int /*<<< orphan*/ ,...) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 
 scalar_t__ ulmax (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
chipc_alloc_resource(device_t dev, device_t child, int type,
    int *rid, rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct chipc_softc		*sc;
	struct chipc_region		*cr;
	struct resource_list_entry	*rle;
	struct resource			*rv;
	struct rman			*rm;
	int				 error;
	bool				 passthrough, isdefault;

	sc = device_get_softc(dev);
	passthrough = (device_get_parent(child) != dev);
	isdefault = RMAN_IS_DEFAULT_RANGE(start, end);
	rle = NULL;

	/* Fetch the resource manager, delegate request if necessary */
	rm = chipc_get_rman(sc, type);
	if (rm == NULL) {
		/* Requested resource type is delegated to our parent */
		rv = bus_generic_rl_alloc_resource(dev, child, type, rid,
		    start, end, count, flags);
		return (rv);
	}

	/* Populate defaults */
	if (!passthrough && isdefault) {
		/* Fetch the resource list entry. */
		rle = resource_list_find(BUS_GET_RESOURCE_LIST(dev, child),
		    type, *rid);
		if (rle == NULL) {
			device_printf(dev,
			    "default resource %#x type %d for child %s "
			    "not found\n", *rid, type,
			    device_get_nameunit(child));			
			return (NULL);
		}
		
		if (rle->res != NULL) {
			device_printf(dev,
			    "resource entry %#x type %d for child %s is busy "
			    "[%d]\n",
			    *rid, type, device_get_nameunit(child),
			    rman_get_flags(rle->res));
			
			return (NULL);
		}

		start = rle->start;
		end = rle->end;
		count = ulmax(count, rle->count);
	}

	/* Locate a mapping region */
	if ((cr = chipc_find_region(sc, start, end)) == NULL) {
		/* Resource requests outside our shared port regions can be
		 * delegated to our parent. */
		rv = bus_generic_rl_alloc_resource(dev, child, type, rid,
		    start, end, count, flags);
		return (rv);
	}

	/*
	 * As a special case, children that map the complete ChipCommon register
	 * block are delegated to our parent.
	 *
	 * The rman API does not support sharing resources that are not
	 * identical in size; since we allocate subregions to various children,
	 * any children that need to map the entire register block (e.g. because
	 * they require access to discontiguous register ranges) must make the
	 * allocation through our parent, where we hold a compatible
	 * RF_SHAREABLE allocation.
	 */
	if (cr == sc->core_region && cr->cr_addr == start &&
	    cr->cr_end == end && cr->cr_count == count)
	{
		rv = bus_generic_rl_alloc_resource(dev, child, type, rid,
		    start, end, count, flags);
		return (rv);
	}

	/* Try to retain a region reference */
	if ((error = chipc_retain_region(sc, cr, RF_ALLOCATED)))
		return (NULL);

	/* Make our rman reservation */
	rv = rman_reserve_resource(rm, start, end, count, flags & ~RF_ACTIVE,
	    child);
	if (rv == NULL) {
		chipc_release_region(sc, cr, RF_ALLOCATED);
		return (NULL);
	}

	rman_set_rid(rv, *rid);

	/* Activate */
	if (flags & RF_ACTIVE) {
		error = bus_activate_resource(child, type, *rid, rv);
		if (error) {
			device_printf(dev,
			    "failed to activate entry %#x type %d for "
				"child %s: %d\n",
			     *rid, type, device_get_nameunit(child), error);

			chipc_release_region(sc, cr, RF_ALLOCATED);
			rman_release_resource(rv);

			return (NULL);
		}
	}

	/* Update child's resource list entry */
	if (rle != NULL) {
		rle->res = rv;
		rle->start = rman_get_start(rv);
		rle->end = rman_get_end(rv);
		rle->count = rman_get_size(rv);
	}

	return (rv);
}