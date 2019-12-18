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
struct agp_intel_softc {int aperture_mask; int current_aperture; int initial_aperture; struct agp_gatt* gatt; } ;
struct agp_gatt {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AGP_INTEL_APSIZE ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int MAX_APSIZE ; 
 struct agp_gatt* agp_alloc_gatt (int /*<<< orphan*/ ) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_intel_commit_gatt (int /*<<< orphan*/ ) ; 
 struct agp_intel_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
agp_intel_attach(device_t dev)
{
	struct agp_intel_softc *sc;
	struct agp_gatt *gatt;
	u_int32_t value;
	int error;

	sc = device_get_softc(dev);

	error = agp_generic_attach(dev);
	if (error)
		return (error);

	/* Determine maximum supported aperture size. */
	value = pci_read_config(dev, AGP_INTEL_APSIZE, 1);
	pci_write_config(dev, AGP_INTEL_APSIZE, MAX_APSIZE, 1);
	sc->aperture_mask = pci_read_config(dev, AGP_INTEL_APSIZE, 1) &
	    MAX_APSIZE;
	pci_write_config(dev, AGP_INTEL_APSIZE, value, 1);
	sc->current_aperture = sc->initial_aperture = AGP_GET_APERTURE(dev);

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
			return (ENOMEM);
		}
	}
	sc->gatt = gatt;

	agp_intel_commit_gatt(dev);

	return (0);
}