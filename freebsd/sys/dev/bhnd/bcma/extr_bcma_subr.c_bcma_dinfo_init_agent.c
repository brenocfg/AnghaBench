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
struct bcma_devinfo {int /*<<< orphan*/ * res_agent; int /*<<< orphan*/  rid_agent; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_AGENT_RID (struct bcma_devinfo*) ; 
 int /*<<< orphan*/  BCMA_DINFO_COREIDX (struct bcma_devinfo*) ; 
 int /*<<< orphan*/ * BHND_BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  BHND_PORT_AGENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_get_port_rid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_get_region_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcma_dinfo_init_agent(device_t bus, device_t child, struct bcma_devinfo *dinfo)
{
	bhnd_addr_t	addr;
	bhnd_size_t	size;
	rman_res_t	r_start, r_count, r_end;
	int		error;

	KASSERT(dinfo->res_agent == NULL, ("double allocation of agent"));

	/* Verify that the agent register block exists and is
	 * mappable */
	if (bhnd_get_port_rid(child, BHND_PORT_AGENT, 0, 0) == -1)
		return (0);	/* nothing to do */

	/* Fetch the address of the agent register block */
	error = bhnd_get_region_addr(child, BHND_PORT_AGENT, 0, 0,
	    &addr, &size);
	if (error) {
		device_printf(bus, "failed fetching agent register block "
		    "address for core %u\n", BCMA_DINFO_COREIDX(dinfo));
		return (error);
	}

	/* Allocate the resource */
	r_start = addr;
	r_count = size;
	r_end = r_start + r_count - 1;

	dinfo->rid_agent = BCMA_AGENT_RID(dinfo);
	dinfo->res_agent = BHND_BUS_ALLOC_RESOURCE(bus, bus, SYS_RES_MEMORY,
	    &dinfo->rid_agent, r_start, r_end, r_count, RF_ACTIVE|RF_SHAREABLE);
	if (dinfo->res_agent == NULL) {
		device_printf(bus, "failed allocating agent register block for "
		    "core %u\n", BCMA_DINFO_COREIDX(dinfo));
		return (ENXIO);
	}

	return (0);
}