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
typedef  int uint32_t ;
struct agp_i810_softc {int /*<<< orphan*/  bdev; int /*<<< orphan*/  sc_bios_allocated_flush_page; int /*<<< orphan*/ * sc_flush_page_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I915_IFPADDR ; 
 int /*<<< orphan*/  agp_i915_chipset_flush_free_page (int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
agp_i915_chipset_flush_teardown(device_t dev)
{
	struct agp_i810_softc *sc;
	uint32_t temp;

	sc = device_get_softc(dev);
	if (sc->sc_flush_page_res == NULL)
		return;
	if (!sc->sc_bios_allocated_flush_page) {
		temp = pci_read_config(sc->bdev, AGP_I915_IFPADDR, 4);
		temp &= ~1;
		pci_write_config(sc->bdev, AGP_I915_IFPADDR, temp, 4);
	}		
	agp_i915_chipset_flush_free_page(dev);
}