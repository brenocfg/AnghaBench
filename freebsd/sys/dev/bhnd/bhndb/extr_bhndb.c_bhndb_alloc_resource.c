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
struct resource_list_entry {int /*<<< orphan*/  count; scalar_t__ end; scalar_t__ start; struct resource* res; } ;
struct resource {int dummy; } ;
struct bhndb_softc {int /*<<< orphan*/  parent_dev; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource* BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RMAN_IS_DEFAULT_RANGE (scalar_t__,scalar_t__) ; 
 struct rman* bhndb_get_rman (struct bhndb_softc*,int /*<<< orphan*/ ,int) ; 
 int bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,...) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 
 scalar_t__ ulmax (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
bhndb_alloc_resource(device_t dev, device_t child, int type,
    int *rid, rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct bhndb_softc		*sc;
	struct resource_list_entry	*rle;
	struct resource			*rv;
	struct rman			*rm;
	int				 error;
	bool				 passthrough, isdefault;

	sc = device_get_softc(dev);
	passthrough = (device_get_parent(child) != dev);
	isdefault = RMAN_IS_DEFAULT_RANGE(start, end);
	rle = NULL;

	/* Fetch the resource manager */
	rm = bhndb_get_rman(sc, child, type);
	if (rm == NULL) {
		/* Delegate to our parent device's bus; the requested
		 * resource type isn't handled locally. */
		return (BUS_ALLOC_RESOURCE(device_get_parent(sc->parent_dev),
		    child, type, rid,  start, end, count, flags));
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
			    "resource entry %#x type %d for child %s is busy\n",
			    *rid, type, device_get_nameunit(child));
			
			return (NULL);
		}

		start = rle->start;
		end = rle->end;
		count = ulmax(count, rle->count);
	}

	/* Validate resource addresses */
	if (start > end || count > ((end - start) + 1))
		return (NULL);

	/* Make our reservation */
	rv = rman_reserve_resource(rm, start, end, count, flags & ~RF_ACTIVE,
	    child);
	if (rv == NULL)
		return (NULL);
	
	rman_set_rid(rv, *rid);

	/* Activate */
	if (flags & RF_ACTIVE) {
		error = bus_activate_resource(child, type, *rid, rv);
		if (error) {
			device_printf(dev,
			    "failed to activate entry %#x type %d for "
				"child %s: %d\n",
			     *rid, type, device_get_nameunit(child), error);

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