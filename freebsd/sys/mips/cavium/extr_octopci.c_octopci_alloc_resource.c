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
struct resource {int dummy; } ;
struct octopci_softc {scalar_t__ sc_io_base; scalar_t__ sc_mem1_base; struct rman sc_io; struct rman sc_mem1; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct resource* bus_generic_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct octopci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octopci_bus_space ; 
 scalar_t__ rman_get_bushandle (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

__attribute__((used)) static struct resource *
octopci_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct octopci_softc *sc;
	struct resource *res;
	struct rman *rm;
	int error;

	sc = device_get_softc(bus);

	switch (type) {
	case SYS_RES_IRQ:
		res = bus_generic_alloc_resource(bus, child, type, rid, start,
		    end, count, flags);
		if (res != NULL)
			return (res);
		return (NULL);
	case SYS_RES_MEMORY:
		rm = &sc->sc_mem1;
		break;
	case SYS_RES_IOPORT:
		rm = &sc->sc_io;
		break;
	default:
		return (NULL);
	}

	res = rman_reserve_resource(rm, start, end, count, flags, child);
	if (res == NULL)
		return (NULL);

	rman_set_rid(res, *rid);
	rman_set_bustag(res, octopci_bus_space);

	switch (type) {
	case SYS_RES_MEMORY:
		rman_set_bushandle(res, sc->sc_mem1_base + rman_get_start(res));
		break;
	case SYS_RES_IOPORT:
		rman_set_bushandle(res, sc->sc_io_base + rman_get_start(res));
#if __mips_n64
		rman_set_virtual(res, (void *)rman_get_bushandle(res));
#else
		/*
		 * XXX
		 * We can't access ports via a 32-bit pointer.
		 */
		rman_set_virtual(res, NULL);
#endif
		break;
	}

	if ((flags & RF_ACTIVE) != 0) {
		error = bus_activate_resource(child, type, *rid, res);
		if (error != 0) {
			rman_release_resource(res);
			return (NULL);
		}
	}

	return (res);
}