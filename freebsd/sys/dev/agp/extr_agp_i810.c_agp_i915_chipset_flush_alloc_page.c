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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct agp_i810_softc {int sc_flush_page_rid; int /*<<< orphan*/  sc_flush_page_vaddr; int /*<<< orphan*/ * sc_flush_page_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_virtual (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
agp_i915_chipset_flush_alloc_page(device_t dev, uint64_t start, uint64_t end)
{
	struct agp_i810_softc *sc;
	device_t vga;

	sc = device_get_softc(dev);
	vga = device_get_parent(dev);
	sc->sc_flush_page_rid = 100;
	sc->sc_flush_page_res = BUS_ALLOC_RESOURCE(device_get_parent(vga), dev,
	    SYS_RES_MEMORY, &sc->sc_flush_page_rid, start, end, PAGE_SIZE,
	    RF_ACTIVE);
	if (sc->sc_flush_page_res == NULL) {
		device_printf(dev, "Failed to allocate flush page at 0x%jx\n",
		    (uintmax_t)start);
		return (EINVAL);
	}
	sc->sc_flush_page_vaddr = rman_get_virtual(sc->sc_flush_page_res);
	if (bootverbose) {
		device_printf(dev, "Allocated flush page phys 0x%jx virt %p\n",
		    (uintmax_t)rman_get_start(sc->sc_flush_page_res),
		    sc->sc_flush_page_vaddr);
	}
	return (0);
}