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
typedef  void* u_long ;
typedef  int u_int ;
struct rman {int dummy; } ;
struct unin_chip_softc {struct rman sc_mem_rman; } ;
struct unin_chip_devinfo {int udi_ninterrupts; int /*<<< orphan*/  udi_resources; void** udi_interrupts; } ;
struct resource_list_entry {void* end; void* start; } ;
struct resource {int dummy; } ;
typedef  void* rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource* BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,void*,void*,void*,int) ; 
 int RF_ACTIVE ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 scalar_t__ bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct unin_chip_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct unin_chip_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int const,int,void*,void*,int) ; 
 struct resource* resource_list_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,void*,void*,void*,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,void*,void*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

__attribute__((used)) static struct resource *
unin_chip_alloc_resource(device_t bus, device_t child, int type, int *rid,
			 rman_res_t start, rman_res_t end, rman_res_t count,
			 u_int flags)
{
	struct		unin_chip_softc *sc;
	int		needactivate;
	struct		resource *rv;
	struct		rman *rm;
	u_long		adjstart, adjend, adjcount;
	struct		unin_chip_devinfo *dinfo;
	struct		resource_list_entry *rle;

	sc = device_get_softc(bus);
	dinfo = device_get_ivars(child);

	needactivate = flags & RF_ACTIVE;
	flags &= ~RF_ACTIVE;

	switch (type) {
	case SYS_RES_MEMORY:
	case SYS_RES_IOPORT:
		rle = resource_list_find(&dinfo->udi_resources, SYS_RES_MEMORY,
					 *rid);
		if (rle == NULL) {
			device_printf(bus, "no rle for %s memory %d\n",
				      device_get_nameunit(child), *rid);
			return (NULL);
		}

		rle->end = rle->end - 1; /* Hack? */

		if (start < rle->start)
			adjstart = rle->start;
		else if (start > rle->end)
			adjstart = rle->end;
		else
			adjstart = start;

		if (end < rle->start)
			adjend = rle->start;
		else if (end > rle->end)
			adjend = rle->end;
		else
			adjend = end;

		adjcount = adjend - adjstart;

		rm = &sc->sc_mem_rman;
		break;

	case SYS_RES_IRQ:
		/* Check for passthrough from subattachments. */
		if (device_get_parent(child) != bus)
			return BUS_ALLOC_RESOURCE(device_get_parent(bus), child,
						  type, rid, start, end, count,
						  flags);

		rle = resource_list_find(&dinfo->udi_resources, SYS_RES_IRQ,
		    *rid);
		if (rle == NULL) {
			if (dinfo->udi_ninterrupts >= 6) {
				device_printf(bus,
					      "%s has more than 6 interrupts\n",
					      device_get_nameunit(child));
				return (NULL);
			}
			resource_list_add(&dinfo->udi_resources, SYS_RES_IRQ,
					  dinfo->udi_ninterrupts, start, start,
					  1);

			dinfo->udi_interrupts[dinfo->udi_ninterrupts] = start;
			dinfo->udi_ninterrupts++;
		}

		return (resource_list_alloc(&dinfo->udi_resources, bus, child,
					    type, rid, start, end, count,
					    flags));
	default:
		device_printf(bus, "unknown resource request from %s\n",
			      device_get_nameunit(child));
		return (NULL);
	}

	rv = rman_reserve_resource(rm, adjstart, adjend, adjcount, flags,
				   child);
	if (rv == NULL) {
		device_printf(bus,
			      "failed to reserve resource %#lx - %#lx (%#lx)"
			      " for %s\n", adjstart, adjend, adjcount,
			      device_get_nameunit(child));
		return (NULL);
	}

	rman_set_rid(rv, *rid);

	if (needactivate) {
		if (bus_activate_resource(child, type, *rid, rv) != 0) {
                        device_printf(bus,
				      "failed to activate resource for %s\n",
				      device_get_nameunit(child));
			rman_release_resource(rv);
			return (NULL);
                }
        }

	return (rv);
}