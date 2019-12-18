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
typedef  int /*<<< orphan*/  u_int ;
struct chipc_softc {scalar_t__ dev; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int ERANGE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RMAN_IS_DEFAULT_RANGE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_get_region_addr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bhnd_port_type_name (int /*<<< orphan*/ ) ; 
 int bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 scalar_t__ device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 

int
chipc_set_mem_resource(struct chipc_softc *sc, device_t child, int rid,
    rman_res_t start, rman_res_t count, u_int port, u_int region)
{
	bhnd_addr_t	region_addr;
	bhnd_size_t	region_size;
	bool		isdefault;
	int		error;

	KASSERT(device_get_parent(child) == sc->dev, ("not a direct child"));
	isdefault = RMAN_IS_DEFAULT_RANGE(start, count);

	/* Fetch region address and size */
	error = bhnd_get_region_addr(sc->dev, BHND_PORT_DEVICE, port,
	    region, &region_addr, &region_size);
	if (error) {
		device_printf(sc->dev,
		    "lookup of %s%u.%u failed: %d\n",
		    bhnd_port_type_name(BHND_PORT_DEVICE), port, region, error);
		return (error);
	}

	/* Populate defaults */
	if (isdefault) {
		start = 0;
		count = region_size;
	}

	/* Verify requested range is mappable */
	if (start > region_size || region_size - start < count) {
		device_printf(sc->dev,
		    "%s%u.%u region cannot map requested range %#jx+%#jx\n",
		    bhnd_port_type_name(BHND_PORT_DEVICE), port, region, start,
		    count);
		return (ERANGE);
	}

	return (bus_set_resource(child, SYS_RES_MEMORY, rid,
	    region_addr + start, count));
}