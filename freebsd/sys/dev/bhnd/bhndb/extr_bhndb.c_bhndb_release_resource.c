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
struct bhndb_softc {int /*<<< orphan*/  parent_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/ * bhndb_get_rman (struct bhndb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ ,int,int) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_release_resource (struct resource*) ; 

__attribute__((used)) static int
bhndb_release_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	struct bhndb_softc		*sc;
	struct resource_list_entry	*rle;
	bool				 passthrough;
	int				 error;

	sc = device_get_softc(dev);
	passthrough = (device_get_parent(child) != dev);

	/* Delegate to our parent device's bus if the requested resource type
	 * isn't handled locally. */
	if (bhndb_get_rman(sc, child, type) == NULL) {
		return (BUS_RELEASE_RESOURCE(device_get_parent(sc->parent_dev),
		    child, type, rid, r));
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