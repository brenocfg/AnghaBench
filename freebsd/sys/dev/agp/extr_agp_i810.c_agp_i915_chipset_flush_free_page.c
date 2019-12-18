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
struct agp_i810_softc {int /*<<< orphan*/ * sc_flush_page_res; int /*<<< orphan*/  sc_flush_page_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
agp_i915_chipset_flush_free_page(device_t dev)
{
	struct agp_i810_softc *sc;
	device_t vga;

	sc = device_get_softc(dev);
	vga = device_get_parent(dev);
	if (sc->sc_flush_page_res == NULL)
		return;
	BUS_DEACTIVATE_RESOURCE(device_get_parent(vga), dev, SYS_RES_MEMORY,
	    sc->sc_flush_page_rid, sc->sc_flush_page_res);
	BUS_RELEASE_RESOURCE(device_get_parent(vga), dev, SYS_RES_MEMORY,
	    sc->sc_flush_page_rid, sc->sc_flush_page_res);
}