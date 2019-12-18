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
struct agp_amd_softc {int initial_aperture; struct agp_amd_gatt* gatt; int /*<<< orphan*/  regs; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct agp_amd_gatt {int /*<<< orphan*/  ag_pdir; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD751_ATTBASE ; 
 int /*<<< orphan*/  AGP_AMD751_MODECTRL ; 
 int /*<<< orphan*/  AGP_AMD751_MODECTRL2 ; 
 int /*<<< orphan*/  AGP_AMD751_MODECTRL2_GPDCE ; 
 int /*<<< orphan*/  AGP_AMD751_MODECTRL_SYNEN ; 
 int AGP_AMD751_REGISTERS ; 
 int /*<<< orphan*/  AGP_AMD751_STATUS ; 
 int AGP_AMD751_STATUS_GCE ; 
 int /*<<< orphan*/  AGP_FLUSH_TLB (int /*<<< orphan*/ ) ; 
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int READ2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WRITE2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_amd_gatt* agp_amd_alloc_gatt (int /*<<< orphan*/ ) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct agp_amd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_amd_attach(device_t dev)
{
	struct agp_amd_softc *sc = device_get_softc(dev);
	struct agp_amd_gatt *gatt;
	int error, rid;

	error = agp_generic_attach(dev);
	if (error)
		return error;

	rid = AGP_AMD751_REGISTERS;
	sc->regs = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
					  RF_ACTIVE);
	if (!sc->regs) {
		agp_generic_detach(dev);
		return ENOMEM;
	}

	sc->bst = rman_get_bustag(sc->regs);
	sc->bsh = rman_get_bushandle(sc->regs);

	sc->initial_aperture = AGP_GET_APERTURE(dev);

	for (;;) {
		gatt = agp_amd_alloc_gatt(dev);
		if (gatt)
			break;

		/*
		 * Probably contigmalloc failure. Try reducing the
		 * aperture so that the gatt size reduces.
		 */
		if (AGP_SET_APERTURE(dev, AGP_GET_APERTURE(dev) / 2))
			return ENOMEM;
	}
	sc->gatt = gatt;

	/* Install the gatt. */
	WRITE4(AGP_AMD751_ATTBASE, gatt->ag_pdir);
	
	/* Enable synchronisation between host and agp. */
	pci_write_config(dev,
			 AGP_AMD751_MODECTRL,
			 AGP_AMD751_MODECTRL_SYNEN, 1);

	/* Set indexing mode for two-level and enable page dir cache */
	pci_write_config(dev,
			 AGP_AMD751_MODECTRL2,
			 AGP_AMD751_MODECTRL2_GPDCE, 1);

	/* Enable the TLB and flush */
	WRITE2(AGP_AMD751_STATUS,
	       READ2(AGP_AMD751_STATUS) | AGP_AMD751_STATUS_GCE);
	AGP_FLUSH_TLB(dev);

	return 0;
}