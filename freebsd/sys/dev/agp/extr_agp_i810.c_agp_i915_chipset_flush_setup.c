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
typedef  int uint32_t ;
struct agp_i810_softc {int sc_bios_allocated_flush_page; int /*<<< orphan*/  bdev; int /*<<< orphan*/  sc_flush_page_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I915_IFPADDR ; 
 int PAGE_SIZE ; 
 int agp_i915_chipset_flush_alloc_page (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bootverbose ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_i915_chipset_flush_setup(device_t dev)
{
	struct agp_i810_softc *sc;
	uint32_t temp;
	int error;

	sc = device_get_softc(dev);
	temp = pci_read_config(sc->bdev, AGP_I915_IFPADDR, 4);
	if ((temp & 1) != 0) {
		temp &= ~1;
		if (bootverbose)
			device_printf(dev,
			    "Found already configured flush page at 0x%jx\n",
			    (uintmax_t)temp);
		sc->sc_bios_allocated_flush_page = 1;
		/*
		 * In the case BIOS initialized the flush pointer (?)
		 * register, expect that BIOS also set up the resource
		 * for the page.
		 */
		error = agp_i915_chipset_flush_alloc_page(dev, temp,
		    temp + PAGE_SIZE - 1);
		if (error != 0)
			return (error);
	} else {
		sc->sc_bios_allocated_flush_page = 0;
		error = agp_i915_chipset_flush_alloc_page(dev, 0, 0xffffffff);
		if (error != 0)
			return (error);
		temp = rman_get_start(sc->sc_flush_page_res);
		pci_write_config(sc->bdev, AGP_I915_IFPADDR, temp | 1, 4);
	}
	return (0);
}