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
struct agp_gatt {int ag_physical; } ;
struct agp_amd64_softc {int* mctrl; int n_mctrl; int initial_aperture; int /*<<< orphan*/  via_agp; struct agp_gatt* gatt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD64_APCTRL ; 
 int AGP_AMD64_APCTRL_DISGARTCPU ; 
 int AGP_AMD64_APCTRL_DISGARTIO ; 
 int AGP_AMD64_APCTRL_GARTEN ; 
 int /*<<< orphan*/  AGP_AMD64_ATTBASE ; 
 int AGP_AMD64_ATTBASE_MASK ; 
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 int AMD64_MAX_MCTRL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int PCI_SLOTMAX ; 
 struct agp_gatt* agp_alloc_gatt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_amd64_nvidia_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_amd64_nvidia_set_aperture (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  agp_amd64_uli_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_amd64_uli_set_aperture (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  agp_amd64_via_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_amd64_via_match () ; 
 int /*<<< orphan*/  agp_amd64_via_set_aperture (int /*<<< orphan*/ ,int) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 struct agp_amd64_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_cfgregwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_amd64_attach(device_t dev)
{
	struct agp_amd64_softc *sc = device_get_softc(dev);
	struct agp_gatt *gatt;
	uint32_t devid;
	int i, n, error;

	for (i = 0, n = 0; i < PCI_SLOTMAX && n < AMD64_MAX_MCTRL; i++) {
		devid = pci_cfgregread(0, i, 3, 0, 4);
		if (devid == 0x11031022 || devid == 0x12031022) {
			sc->mctrl[n] = i;
			n++;
		}
	}
	if (n == 0)
		return (ENXIO);

	sc->n_mctrl = n;

	if (bootverbose)
		device_printf(dev, "%d Miscellaneous Control unit(s) found.\n",
		    sc->n_mctrl);

	if ((error = agp_generic_attach(dev)))
		return (error);

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
			return (ENOMEM);
		}
	}
	sc->gatt = gatt;

	switch (pci_get_vendor(dev)) {
	case 0x10b9:	/* ULi */
		agp_amd64_uli_init(dev);
		if (agp_amd64_uli_set_aperture(dev, sc->initial_aperture))
			return (ENXIO);
		break;

	case 0x10de:	/* nVidia */
		agp_amd64_nvidia_init(dev);
		if (agp_amd64_nvidia_set_aperture(dev, sc->initial_aperture))
			return (ENXIO);
		break;

	case 0x1106:	/* VIA */
		sc->via_agp = agp_amd64_via_match();
		if (sc->via_agp) {
			agp_amd64_via_init(dev);
			if (agp_amd64_via_set_aperture(dev,
			    sc->initial_aperture))
				return (ENXIO);
		}
		break;
	}

	/* Install the gatt and enable aperture. */
	for (i = 0; i < sc->n_mctrl; i++) {
		pci_cfgregwrite(0, sc->mctrl[i], 3, AGP_AMD64_ATTBASE,
		    (uint32_t)(gatt->ag_physical >> 8) & AGP_AMD64_ATTBASE_MASK,
		    4);
		pci_cfgregwrite(0, sc->mctrl[i], 3, AGP_AMD64_APCTRL,
		    (pci_cfgregread(0, sc->mctrl[i], 3, AGP_AMD64_APCTRL, 4) |
		    AGP_AMD64_APCTRL_GARTEN) &
		    ~(AGP_AMD64_APCTRL_DISGARTCPU | AGP_AMD64_APCTRL_DISGARTIO),
		    4);
	}

	return (0);
}