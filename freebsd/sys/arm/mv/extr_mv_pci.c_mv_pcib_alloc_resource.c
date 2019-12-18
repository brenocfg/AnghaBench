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
struct mv_pcib_softc {int sc_mem_base; int sc_mem_size; int /*<<< orphan*/  ap_segment; struct rman sc_mem_rman; struct rman sc_io_rman; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct resource* BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int) ; 
#define  PCI_RES_BUS 130 
 int RF_ACTIVE ; 
 scalar_t__ RMAN_IS_DEFAULT_RANGE (int,int) ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 scalar_t__ bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct mv_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 struct resource* pci_domain_alloc_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int) ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

__attribute__((used)) static struct resource *
mv_pcib_alloc_resource(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct mv_pcib_softc *sc = device_get_softc(dev);
	struct rman *rm = NULL;
	struct resource *res;

	switch (type) {
	case SYS_RES_IOPORT:
		rm = &sc->sc_io_rman;
		break;
	case SYS_RES_MEMORY:
		rm = &sc->sc_mem_rman;
		break;
#ifdef PCI_RES_BUS
	case PCI_RES_BUS:
		return (pci_domain_alloc_bus(sc->ap_segment, child, rid, start,
		    end, count, flags));
#endif
	default:
		return (BUS_ALLOC_RESOURCE(device_get_parent(dev), dev,
		    type, rid, start, end, count, flags));
	}

	if (RMAN_IS_DEFAULT_RANGE(start, end)) {
		start = sc->sc_mem_base;
		end = sc->sc_mem_base + sc->sc_mem_size - 1;
		count = sc->sc_mem_size;
	}

	if ((start < sc->sc_mem_base) || (start + count - 1 != end) ||
	    (end > sc->sc_mem_base + sc->sc_mem_size - 1))
		return (NULL);

	res = rman_reserve_resource(rm, start, end, count, flags, child);
	if (res == NULL)
		return (NULL);

	rman_set_rid(res, *rid);
	rman_set_bustag(res, fdtbus_bs_tag);
	rman_set_bushandle(res, start);

	if (flags & RF_ACTIVE)
		if (bus_activate_resource(child, type, *rid, res)) {
			rman_release_resource(res);
			return (NULL);
		}

	return (res);
}