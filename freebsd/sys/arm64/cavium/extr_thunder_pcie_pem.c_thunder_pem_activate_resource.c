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
struct thunder_pem_softc {int /*<<< orphan*/  ranges; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int bus_space_map (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct thunder_pem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmap_bus ; 
 scalar_t__ range_addr_pci_to_phys (int /*<<< orphan*/ ,scalar_t__) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_deactivate_resource (struct resource*) ; 
 scalar_t__ rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

__attribute__((used)) static int
thunder_pem_activate_resource(device_t dev, device_t child, int type, int rid,
    struct resource *r)
{
	int err;
	bus_addr_t paddr;
	bus_size_t psize;
	bus_space_handle_t vaddr;
	struct thunder_pem_softc *sc;

	if ((err = rman_activate_resource(r)) != 0)
		return (err);

	sc = device_get_softc(dev);

	/*
	 * If this is a memory resource, map it into the kernel.
	 */
	if (type == SYS_RES_MEMORY || type == SYS_RES_IOPORT) {
		paddr = (bus_addr_t)rman_get_start(r);
		psize = (bus_size_t)rman_get_size(r);

		paddr = range_addr_pci_to_phys(sc->ranges, paddr);

		err = bus_space_map(&memmap_bus, paddr, psize, 0, &vaddr);
		if (err != 0) {
			rman_deactivate_resource(r);
			return (err);
		}
		rman_set_bustag(r, &memmap_bus);
		rman_set_virtual(r, (void *)vaddr);
		rman_set_bushandle(r, vaddr);
	}
	return (0);
}