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
struct chipc_softc {int dummy; } ;
struct chipc_region {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int bus_generic_deactivate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct chipc_region* chipc_find_region (struct chipc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rman* chipc_get_rman (struct chipc_softc*,int) ; 
 int /*<<< orphan*/  chipc_release_region (struct chipc_softc*,struct chipc_region*,int /*<<< orphan*/ ) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_deactivate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_end (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 

__attribute__((used)) static int
chipc_deactivate_resource(device_t dev, device_t child, int type,
    int rid, struct resource *r)
{
	struct chipc_softc	*sc;
	struct chipc_region	*cr;
	struct rman		*rm;
	int			 error;

	sc = device_get_softc(dev);

	/* Handled by parent bus? */
	rm = chipc_get_rman(sc, type);
	if (rm == NULL || !rman_is_region_manager(r, rm)) {
		return (bus_generic_deactivate_resource(dev, child, type, rid,
		    r));
	}

	/* Find the corresponding chipc region */
	cr = chipc_find_region(sc, rman_get_start(r), rman_get_end(r));
	if (cr == NULL)
		return (EINVAL);

	/* Mark inactive */
	if ((error = rman_deactivate_resource(r)))
		return (error);

	/* Drop associated RF_ACTIVE reference */
	chipc_release_region(sc, cr, RF_ACTIVE);

	return (0);
}