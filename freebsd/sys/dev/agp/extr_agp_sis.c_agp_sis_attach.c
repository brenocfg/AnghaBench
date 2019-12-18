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
struct agp_sis_softc {int initial_aperture; struct agp_gatt* gatt; } ;
struct agp_gatt {int ag_physical; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AGP_SIS_ATTBASE ; 
 int /*<<< orphan*/  AGP_SIS_TLBCTRL ; 
 int /*<<< orphan*/  AGP_SIS_WINCTRL ; 
 int ENOMEM ; 
 struct agp_gatt* agp_alloc_gatt (int /*<<< orphan*/ ) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 struct agp_sis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_sis_attach(device_t dev)
{
	struct agp_sis_softc *sc = device_get_softc(dev);
	struct agp_gatt *gatt;
	int error;

	error = agp_generic_attach(dev);
	if (error)
		return error;

	sc->initial_aperture = AGP_GET_APERTURE(dev);

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
	pci_write_config(dev, AGP_SIS_ATTBASE, gatt->ag_physical, 4);
	
	/* Enable the aperture. */
	pci_write_config(dev, AGP_SIS_WINCTRL,
			 pci_read_config(dev, AGP_SIS_WINCTRL, 1) | 3, 1);

	/*
	 * Enable the TLB and make it automatically invalidate entries
	 * when the GATT is written.
	 */
	pci_write_config(dev, AGP_SIS_TLBCTRL, 0x05, 1);

	return 0;
}