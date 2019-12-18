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
struct resource_list_entry {scalar_t__ start; scalar_t__ end; scalar_t__ count; struct resource* res; } ;
struct resource {int dummy; } ;
struct ofwbus_softc {struct rman sc_mem_rman; struct rman sc_intr_rman; } ;
typedef  scalar_t__ rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_GET_RESOURCE_LIST (scalar_t__,scalar_t__) ; 
 int RF_ACTIVE ; 
 int RMAN_IS_DEFAULT_RANGE (scalar_t__,scalar_t__) ; 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_activate_resource (scalar_t__,int,int,struct resource*) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct ofwbus_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 
 scalar_t__ ummax (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct resource *
ofwbus_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct ofwbus_softc *sc;
	struct rman *rm;
	struct resource *rv;
	struct resource_list_entry *rle;
	int isdefault, passthrough;

	isdefault = RMAN_IS_DEFAULT_RANGE(start, end);
	passthrough = (device_get_parent(child) != bus);
	sc = device_get_softc(bus);
	rle = NULL;
	if (!passthrough && isdefault) {
		rle = resource_list_find(BUS_GET_RESOURCE_LIST(bus, child),
		    type, *rid);
		if (rle == NULL) {
			if (bootverbose)
				device_printf(bus, "no default resources for "
				    "rid = %d, type = %d\n", *rid, type);
			return (NULL);
		}
		start = rle->start;
		count = ummax(count, rle->count);
		end = ummax(rle->end, start + count - 1);
	}

	switch (type) {
	case SYS_RES_IRQ:
		rm = &sc->sc_intr_rman;
		break;
	case SYS_RES_MEMORY:
		rm = &sc->sc_mem_rman;
		break;
	default:
		return (NULL);
	}

	rv = rman_reserve_resource(rm, start, end, count, flags & ~RF_ACTIVE,
	    child);
	if (rv == NULL)
		return (NULL);
	rman_set_rid(rv, *rid);

	if ((flags & RF_ACTIVE) != 0 && bus_activate_resource(child, type,
	    *rid, rv) != 0) {
		rman_release_resource(rv);
		return (NULL);
	}

	if (!passthrough && rle != NULL) {
		rle->res = rv;
		rle->start = rman_get_start(rv);
		rle->end = rman_get_end(rv);
		rle->count = rle->end - rle->start + 1;
	}

	return (rv);
}