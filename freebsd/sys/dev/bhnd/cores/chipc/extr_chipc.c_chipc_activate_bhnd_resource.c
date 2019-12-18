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
struct chipc_softc {int dummy; } ;
struct bhnd_resource {int direct; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int bhnd_bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct bhnd_resource*) ; 
 struct rman* chipc_get_rman (struct chipc_softc*,int) ; 
 int chipc_try_activate_resource (struct chipc_softc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_is_region_manager (int /*<<< orphan*/ ,struct rman*) ; 

__attribute__((used)) static int
chipc_activate_bhnd_resource(device_t dev, device_t child, int type,
    int rid, struct bhnd_resource *r)
{
	struct chipc_softc	*sc;
	struct rman		*rm;
	int			 error;

	sc = device_get_softc(dev);
	
	/* Delegate non-locally managed resources to parent */
	rm = chipc_get_rman(sc, type);
	if (rm == NULL || !rman_is_region_manager(r->res, rm)) {
		return (bhnd_bus_generic_activate_resource(dev, child, type,
		    rid, r));
	}

	/* Try activating the chipc region resource */
	error = chipc_try_activate_resource(sc, child, type, rid, r->res,
	    false);
	if (error)
		return (error);

	/* Mark the child resource as direct according to the returned resource
	 * state */
	if (rman_get_flags(r->res) & RF_ACTIVE)
		r->direct = true;

	return (0);
}