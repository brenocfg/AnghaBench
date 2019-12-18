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
struct resource {int dummy; } ;
struct ebus_softc {int sc_flags; int sc_nrange; struct ebus_rinfo* sc_rinfo; } ;
struct ebus_rinfo {struct resource* eri_res; int /*<<< orphan*/  eri_rman; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int EBUS_PCI ; 
 int EINVAL ; 
 int SYS_RES_IRQ ; 
 int bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 scalar_t__ rman_is_region_manager (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ebus_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{
	struct ebus_softc *sc;
	struct ebus_rinfo *eri;
	bus_space_tag_t bt;
	bus_space_handle_t bh;
	int i, rv;

	sc = device_get_softc(bus);
	if ((sc->sc_flags & EBUS_PCI) != 0 && type != SYS_RES_IRQ) {
		for (i = 0; i < sc->sc_nrange; i++) {
			eri = &sc->sc_rinfo[i];
			if (rman_is_region_manager(res, &eri->eri_rman) != 0) {
				bt = rman_get_bustag(eri->eri_res);
				rv = bus_space_subregion(bt,
				    rman_get_bushandle(eri->eri_res),
				    rman_get_start(res) -
				    rman_get_start(eri->eri_res),
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