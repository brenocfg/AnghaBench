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
struct agp_apple_softc {int /*<<< orphan*/  gatt; scalar_t__ needs_2x_reset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIN_AGP_GART_2XRESET ; 
 int /*<<< orphan*/  UNIN_AGP_GART_CONTROL ; 
 int /*<<< orphan*/  UNIN_AGP_GART_INVAL ; 
 int /*<<< orphan*/  agp_free_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_gatt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_res (int /*<<< orphan*/ ) ; 
 struct agp_apple_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_apple_detach(device_t dev)
{
	struct agp_apple_softc *sc = device_get_softc(dev);

	agp_free_cdev(dev);

	/* Disable the aperture and TLB */
	pci_write_config(dev, UNIN_AGP_GART_CONTROL, UNIN_AGP_GART_INVAL, 4);
	pci_write_config(dev, UNIN_AGP_GART_CONTROL, 0, 4);

	if (sc->needs_2x_reset) {
		pci_write_config(dev, UNIN_AGP_GART_CONTROL,
		    UNIN_AGP_GART_2XRESET, 4);
		pci_write_config(dev, UNIN_AGP_GART_CONTROL, 0, 4);
	}

	AGP_SET_APERTURE(dev, 0);

	agp_free_gatt(sc->gatt);
	agp_free_res(dev);
	return 0;
}