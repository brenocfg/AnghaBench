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
typedef  int u_int32_t ;
struct agp_gatt {int ag_physical; } ;
struct agp_ali_softc {int initial_aperture; struct agp_gatt* gatt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_ALI_ATTBASE ; 
 int /*<<< orphan*/  AGP_ALI_TLBCTRL ; 
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct agp_gatt* agp_alloc_gatt (int /*<<< orphan*/ ) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 struct agp_ali_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_ali_attach(device_t dev)
{
	struct agp_ali_softc *sc = device_get_softc(dev);
	struct agp_gatt *gatt;
	int error;
	u_int32_t attbase;

	error = agp_generic_attach(dev);
	if (error)
		return error;

	sc->initial_aperture = AGP_GET_APERTURE(dev);
	if (sc->initial_aperture == 0) {
		device_printf(dev, "bad initial aperture size, disabling\n");
		return ENXIO;
	}

	for (;;) {
		gatt = agp_alloc_gatt(dev);
		if (gatt)
			break;

		/*
		 * Probably contigmalloc failure. Try reducing the
		 * aperture so that the gatt size reduces.
		 */
		if (AGP_SET_APERTURE(dev, AGP_GET_APERTURE(dev) / 2)) {
			agp_generic_detach(dev);
			return ENOMEM;
		}
	}
	sc->gatt = gatt;

	/* Install the gatt. */
	attbase = pci_read_config(dev, AGP_ALI_ATTBASE, 4);
	pci_write_config(dev, AGP_ALI_ATTBASE, gatt->ag_physical |
	    (attbase & 0xfff), 4);
	
	/* Enable the TLB. */
	pci_write_config(dev, AGP_ALI_TLBCTRL, 0x10, 1);

	return 0;
}