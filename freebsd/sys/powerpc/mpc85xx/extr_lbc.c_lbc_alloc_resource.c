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
struct resource_list_entry {scalar_t__ count; scalar_t__ start; } ;
struct resource {int dummy; } ;
struct lbc_softc {struct rman sc_rman; } ;
struct lbc_devinfo {int di_bank; int /*<<< orphan*/  di_res; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int /*<<< orphan*/  RMAN_IS_DEFAULT_RANGE (scalar_t__,scalar_t__) ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bs_be_tag ; 
 scalar_t__ bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct resource* bus_alloc_resource (int /*<<< orphan*/ ,int,int*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 struct lbc_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct lbc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

__attribute__((used)) static struct resource *
lbc_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct lbc_softc *sc;
	struct lbc_devinfo *di;
	struct resource_list_entry *rle;
	struct resource *res;
	struct rman *rm;
	int needactivate;

	/* We only support default allocations. */
	if (!RMAN_IS_DEFAULT_RANGE(start, end))
		return (NULL);

	sc = device_get_softc(bus);
	if (type == SYS_RES_IRQ)
		return (bus_alloc_resource(bus, type, rid, start, end, count,
		    flags));

	/*
	 * Request for the default allocation with a given rid: use resource
	 * list stored in the local device info.
	 */
	if ((di = device_get_ivars(child)) == NULL)
		return (NULL);

	if (type == SYS_RES_IOPORT)
		type = SYS_RES_MEMORY;

	rid = &di->di_bank;

	rle = resource_list_find(&di->di_res, type, *rid);
	if (rle == NULL) {
		device_printf(bus, "no default resources for "
		    "rid = %d, type = %d\n", *rid, type);
		return (NULL);
	}
	start = rle->start;
	count = rle->count;
	end = start + count - 1;

	sc = device_get_softc(bus);

	needactivate = flags & RF_ACTIVE;
	flags &= ~RF_ACTIVE;

	rm = &sc->sc_rman;

	res = rman_reserve_resource(rm, start, end, count, flags, child);
	if (res == NULL) {
		device_printf(bus, "failed to reserve resource %#jx - %#jx "
		    "(%#jx)\n", start, end, count);
		return (NULL);
	}

	rman_set_rid(res, *rid);
	rman_set_bustag(res, &bs_be_tag);
	rman_set_bushandle(res, rman_get_start(res));

	if (needactivate)
		if (bus_activate_resource(child, type, *rid, res)) {
			device_printf(child, "resource activation failed\n");
			rman_release_resource(res);
			return (NULL);
		}

	return (res);
}