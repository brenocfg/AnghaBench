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
struct bhndb_dw_alloc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_ADDRSPACE_BRIDGED ; 
 int /*<<< orphan*/  BHNDB_LOCK (struct bhndb_softc*) ; 
 int /*<<< orphan*/  BHNDB_UNLOCK (struct bhndb_softc*) ; 
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int ENXIO ; 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 struct bhndb_dw_alloc* bhndb_dw_find_resource (int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  bhndb_dw_release (int /*<<< orphan*/ ,struct bhndb_dw_alloc*,struct resource*) ; 
 int /*<<< orphan*/  bhndb_get_addrspace (struct bhndb_softc*,int /*<<< orphan*/ ) ; 
 struct rman* bhndb_get_rman (struct bhndb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int rman_deactivate_resource (struct resource*) ; 

__attribute__((used)) static int
bhndb_deactivate_resource(device_t dev, device_t child, int type,
    int rid, struct resource *r)
{
	struct bhndb_dw_alloc	*dwa;
	struct bhndb_softc	*sc;
	struct rman		*rm;
	int			 error;

	sc = device_get_softc(dev);

	/* Delegate directly to our parent device's bus if the requested
	 * resource type isn't handled locally. */
	rm = bhndb_get_rman(sc, child, type);
	if (rm == NULL) {
		return (BUS_DEACTIVATE_RESOURCE(
		    device_get_parent(sc->parent_dev), child, type, rid, r));
	}

	/* Mark inactive */
	if ((error = rman_deactivate_resource(r)))
		return (error);

	switch (type) {
	case SYS_RES_IRQ:
		/* No bridge-level state to be freed */
		return (0);

	case SYS_RES_MEMORY:
		/* Free any dynamic window allocation. */
		if (bhndb_get_addrspace(sc, child) == BHNDB_ADDRSPACE_BRIDGED) {
			BHNDB_LOCK(sc);
			dwa = bhndb_dw_find_resource(sc->bus_res, r);
			if (dwa != NULL)
				bhndb_dw_release(sc->bus_res, dwa, r);
			BHNDB_UNLOCK(sc);
		}

		return (0);

	default:
		device_printf(dev, "unsupported resource type %d\n", type);
		return (ENXIO);
	}
}