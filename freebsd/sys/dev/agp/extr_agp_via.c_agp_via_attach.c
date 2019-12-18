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
struct agp_via_softc {int initial_aperture; scalar_t__* regs; struct agp_gatt* gatt; } ;
struct agp_gatt {int ag_physical; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AGP_CAPID ; 
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AGP_VIA_AGPSEL ; 
 int ENOMEM ; 
 size_t REG_ATTBASE ; 
 size_t REG_GARTCTRL ; 
 struct agp_gatt* agp_alloc_gatt (int /*<<< orphan*/ ) ; 
 scalar_t__ agp_find_caps (int /*<<< orphan*/ ) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 struct agp_via_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__* via_v2_regs ; 
 scalar_t__* via_v3_regs ; 

__attribute__((used)) static int
agp_via_attach(device_t dev)
{
	struct agp_via_softc *sc = device_get_softc(dev);
	struct agp_gatt *gatt;
	int error;
	u_int32_t agpsel;
	u_int32_t capid;

	sc->regs = via_v2_regs;

	/* Look at the capability register to see if we handle AGP3 */
	capid = pci_read_config(dev, agp_find_caps(dev) + AGP_CAPID, 4);
	if (((capid >> 20) & 0x0f) >= 3) { 
		agpsel = pci_read_config(dev, AGP_VIA_AGPSEL, 1);
		if ((agpsel & (1 << 1)) == 0)
			sc->regs = via_v3_regs;
	}
	
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

	if (sc->regs == via_v2_regs) {
		/* Install the gatt. */
		pci_write_config(dev, sc->regs[REG_ATTBASE], gatt->ag_physical | 3, 4);
		
		/* Enable the aperture. */
		pci_write_config(dev, sc->regs[REG_GARTCTRL], 0x0f, 4);
	} else {
		u_int32_t gartctrl;

		/* Install the gatt. */
		pci_write_config(dev, sc->regs[REG_ATTBASE], gatt->ag_physical, 4);
		
		/* Enable the aperture. */
		gartctrl = pci_read_config(dev, sc->regs[REG_GARTCTRL], 4);
		pci_write_config(dev, sc->regs[REG_GARTCTRL], gartctrl | (3 << 7), 4);
	}

	device_printf(dev, "aperture size is %dM\n",
		sc->initial_aperture / 1024 / 1024);

	return 0;
}