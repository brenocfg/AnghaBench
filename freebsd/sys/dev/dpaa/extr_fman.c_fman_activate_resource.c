#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_2__ {int nranges; } ;
struct fman_softc {struct resource* mem_res; int /*<<< orphan*/  rman; TYPE_1__ sc_base; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int EINVAL ; 
 int SYS_RES_IRQ ; 
 int bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fman_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 scalar_t__ rman_is_region_manager (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 

int
fman_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{
	struct fman_softc *sc;
	bus_space_tag_t bt;
	bus_space_handle_t bh;
	int i, rv;

	sc = device_get_softc(bus);
	if (type != SYS_RES_IRQ) {
		for (i = 0; i < sc->sc_base.nranges; i++) {
			if (rman_is_region_manager(res, &sc->rman) != 0) {
				bt = rman_get_bustag(sc->mem_res);
				rv = bus_space_subregion(bt,
				    rman_get_bushandle(sc->mem_res),
				    rman_get_start(res) -
				    rman_get_start(sc->mem_res),
				    rman_get_size(res), &bh);
				if (rv != 0)
					return (rv);
				rman_set_bustag(res, bt);
				rman_set_bushandle(res, bh);
				return (rman_activate_resource(res));
			}
		}
		return (EINVAL);
	}
	return (bus_generic_activate_resource(bus, child, type, rid, res));
}