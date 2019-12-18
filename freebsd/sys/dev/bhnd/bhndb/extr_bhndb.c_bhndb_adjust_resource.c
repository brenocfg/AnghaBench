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
struct resource {int dummy; } ;
struct bhndb_softc {int /*<<< orphan*/  bus_res; int /*<<< orphan*/  parent_dev; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_LOCK (struct bhndb_softc*) ; 
 int /*<<< orphan*/  BHNDB_UNLOCK (struct bhndb_softc*) ; 
 int BUS_ADJUST_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int ENXIO ; 
 int RF_ACTIVE ; 
 int bhndb_find_resource_limits (int /*<<< orphan*/ ,int,struct resource*,scalar_t__*,scalar_t__*) ; 
 struct rman* bhndb_get_rman (struct bhndb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_adjust_resource (struct resource*,scalar_t__,scalar_t__) ; 
 int rman_get_flags (struct resource*) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 

__attribute__((used)) static int
bhndb_adjust_resource(device_t dev, device_t child, int type,
    struct resource *r, rman_res_t start, rman_res_t end)
{
	struct bhndb_softc		*sc;
	struct rman			*rm;
	rman_res_t			 mstart, mend;
	int				 error;
	
	sc = device_get_softc(dev);
	error = 0;

	/* Delegate to our parent device's bus if the requested resource type
	 * isn't handled locally. */
	rm = bhndb_get_rman(sc, child, type);
	if (rm == NULL) {
		return (BUS_ADJUST_RESOURCE(device_get_parent(sc->parent_dev),
		    child, type, r, start, end));
	}

	/* Verify basic constraints */
	if (end <= start)
		return (EINVAL);

	if (!rman_is_region_manager(r, rm))
		return (ENXIO);

	BHNDB_LOCK(sc);

	/* If not active, allow any range permitted by the resource manager */
	if (!(rman_get_flags(r) & RF_ACTIVE))
		goto done;

	/* Otherwise, the range is limited by the bridged resource mapping */
	error = bhndb_find_resource_limits(sc->bus_res, type, r, &mstart,
	    &mend);
	if (error)
		goto done;

	if (start < mstart || end > mend) {
		error = EINVAL;
		goto done;
	}

	/* Fall through */
done:
	if (!error)
		error = rman_adjust_resource(r, start, end);

	BHNDB_UNLOCK(sc);
	return (error);
}