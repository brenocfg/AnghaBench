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
struct agp_ati_softc {int is_rs300; int initial_aperture; int ag_pdir; int /*<<< orphan*/  regs; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FLUSH_TLB (int /*<<< orphan*/ ) ; 
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATI_GART_BASE ; 
 int /*<<< orphan*/  ATI_GART_FEATURE_ID ; 
 int ATI_GART_MMADDR ; 
 int ATI_RS100_APSIZE ; 
 int ATI_RS100_IG_AGPMODE ; 
 int ATI_RS300_APSIZE ; 
 int ATI_RS300_IG_AGPMODE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WRITE4 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ agp_ati_alloc_gatt (int /*<<< orphan*/ ) ; 
 int agp_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct agp_ati_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_ati_attach(device_t dev)
{
	struct agp_ati_softc *sc = device_get_softc(dev);
	int error, rid;
	u_int32_t temp;
	u_int32_t apsize_reg, agpmode_reg;

	error = agp_generic_attach(dev);
	if (error)
		return error;

	switch (pci_get_devid(dev)) {
	case 0xcab01002: /* ATI RS100 AGP bridge */
	case 0xcab21002: /* ATI RS200 AGP bridge */
	case 0xcbb21002: /* ATI RS200M AGP bridge */
	case 0xcab31002: /* ATI RS250 AGP bridge */
		sc->is_rs300 = 0;
		apsize_reg = ATI_RS100_APSIZE;
		agpmode_reg = ATI_RS100_IG_AGPMODE;
		break;
	case 0x58301002: /* ATI RS300_100 AGP bridge */
	case 0x58311002: /* ATI RS300_133 AGP bridge */
	case 0x58321002: /* ATI RS300_166 AGP bridge */
	case 0x58331002: /* ATI RS300_200 AGP bridge */
		sc->is_rs300 = 1;
		apsize_reg = ATI_RS300_APSIZE;
		agpmode_reg = ATI_RS300_IG_AGPMODE;
		break;
	default:
		/* Unknown chipset */
		return EINVAL;
	}

	rid = ATI_GART_MMADDR;
	sc->regs = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (!sc->regs) {
		agp_generic_detach(dev);
		return ENOMEM;
	}

	sc->bst = rman_get_bustag(sc->regs);
	sc->bsh = rman_get_bushandle(sc->regs);

	sc->initial_aperture = AGP_GET_APERTURE(dev);

	for (;;) {
		if (agp_ati_alloc_gatt(dev) == 0)
			break;

		/*
		 * Probably contigmalloc failure. Try reducing the
		 * aperture so that the gatt size reduces.
		 */
		if (AGP_SET_APERTURE(dev, AGP_GET_APERTURE(dev) / 2))
			return ENOMEM;
	}

	temp = pci_read_config(dev, apsize_reg, 4);
	pci_write_config(dev, apsize_reg, temp | 1, 4);

	pci_write_config(dev, agpmode_reg, 0x20000, 4);

	WRITE4(ATI_GART_FEATURE_ID, 0x00060000);

	temp = pci_read_config(dev, 4, 4);	/* XXX: Magic reg# */
	pci_write_config(dev, 4, temp | (1 << 14), 4);

	WRITE4(ATI_GART_BASE, sc->ag_pdir);

	AGP_FLUSH_TLB(dev);

	return 0;
}