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
struct agp_apple_softc {int needs_2x_reset; int u3; int aperture; scalar_t__ gatt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FLUSH_TLB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  UNIN_AGP_BASE_ADDR ; 
 scalar_t__ agp_alloc_gatt (int /*<<< orphan*/ ) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_set_aperture_resource (int /*<<< orphan*/ ,int) ; 
 struct agp_apple_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_apple_attach(device_t dev)
{
	struct agp_apple_softc *sc = device_get_softc(dev);
	int error;

	/* Record quirks */
	sc->needs_2x_reset = 0;
	sc->u3 = 0;
	switch (pci_get_devid(dev)) {
	case 0x0020106b:
	case 0x0027106b:
		sc->needs_2x_reset = 1;
		break;
	case 0x004b106b:
	case 0x0058106b:
	case 0x0059106b:
		sc->u3 = 1;
		break;
	}

	/* Set the aperture bus address base (must be 0) */
	pci_write_config(dev, UNIN_AGP_BASE_ADDR, 0, 4);
	agp_set_aperture_resource(dev, -1);

	error = agp_generic_attach(dev);
	if (error)
		return (error);

	sc->aperture = 256*1024*1024;

	for (sc->aperture = 256*1024*1024; sc->aperture >= 4*1024*1024;
	    sc->aperture /= 2) {
		sc->gatt = agp_alloc_gatt(dev);
		if (sc->gatt)
			break;
	}
	if (sc->aperture < 4*1024*1024) {
		agp_generic_detach(dev);
		return ENOMEM;
	}

	/* Install the gatt. */
	AGP_SET_APERTURE(dev, sc->aperture);

	/* XXX: U3 scratch page? */
	
	/* Enable the aperture and TLB. */
	AGP_FLUSH_TLB(dev);

	return (0);
}