#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  as_aperture; } ;
struct agp_nvidia_softc {int wbc_mask; int initial_aperture; int num_dirs; int num_active_entries; int pg_offset; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * mc2_dev; struct agp_gatt* gatt; int /*<<< orphan*/ * bdev; TYPE_1__ agp; int /*<<< orphan*/ * mc1_dev; } ;
struct agp_gatt {int ag_physical; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int AGP_GET_APERTURE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AGP_NVIDIA_0_APSIZE ; 
 int /*<<< orphan*/  AGP_NVIDIA_2_APBASE ; 
 int /*<<< orphan*/  AGP_NVIDIA_2_APLIMIT ; 
 int /*<<< orphan*/  AGP_NVIDIA_2_ATTBASE (int) ; 
 int /*<<< orphan*/  AGP_NVIDIA_2_GARTCTRL ; 
 int /*<<< orphan*/  AGP_NVIDIA_3_APBASE ; 
 int /*<<< orphan*/  AGP_NVIDIA_3_APLIMIT ; 
 scalar_t__ AGP_SET_APERTURE (int /*<<< orphan*/ *,int) ; 
 int ENODEV ; 
 int ENOMEM ; 
#define  NVIDIA_DEVICEID_NFORCE 129 
#define  NVIDIA_DEVICEID_NFORCE2 128 
 int PAGE_SIZE ; 
 struct agp_gatt* agp_alloc_gatt (int /*<<< orphan*/ *) ; 
 int agp_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  agp_generic_detach (int /*<<< orphan*/ *) ; 
 struct agp_nvidia_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int nvidia_init_iorr (int,int) ; 
 void* pci_find_bsf (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ *) ; 
 int pci_get_device (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int rman_get_start (int /*<<< orphan*/ ) ; 
 int rounddown2 (int,int) ; 

__attribute__((used)) static int
agp_nvidia_attach (device_t dev)
{
	struct agp_nvidia_softc *sc = device_get_softc(dev);
	struct agp_gatt *gatt;
	u_int32_t apbase;
	u_int32_t aplimit;
	u_int32_t temp;
	int size;
	int i;
	int error;

	switch (pci_get_device(dev)) {
	case NVIDIA_DEVICEID_NFORCE:
		sc->wbc_mask = 0x00010000;
		break;
	case NVIDIA_DEVICEID_NFORCE2:
		sc->wbc_mask = 0x80000000;
		break;
	default:
		device_printf(dev, "Bad chip id\n");
		return (ENODEV);
	}

	/* AGP Controller */
	sc->dev = dev;

	/* Memory Controller 1 */
	sc->mc1_dev = pci_find_bsf(pci_get_bus(dev), 0, 1);
	if (sc->mc1_dev == NULL) {
		device_printf(dev,
			"Unable to find NVIDIA Memory Controller 1.\n");
		return (ENODEV);
	}

	/* Memory Controller 2 */
	sc->mc2_dev = pci_find_bsf(pci_get_bus(dev), 0, 2);
	if (sc->mc2_dev == NULL) {
		device_printf(dev,
			"Unable to find NVIDIA Memory Controller 2.\n");
		return (ENODEV);
	}

	/* AGP Host to PCI Bridge */
	sc->bdev = pci_find_bsf(pci_get_bus(dev), 30, 0);
	if (sc->bdev == NULL) {
		device_printf(dev,
			"Unable to find NVIDIA AGP Host to PCI Bridge.\n");
		return (ENODEV);
	}

	error = agp_generic_attach(dev);
	if (error)
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
		if (AGP_SET_APERTURE(dev, AGP_GET_APERTURE(dev) / 2))
			goto fail;
	}
	sc->gatt = gatt;

	apbase = rman_get_start(sc->agp.as_aperture);
	aplimit = apbase + AGP_GET_APERTURE(dev) - 1;
	pci_write_config(sc->mc2_dev, AGP_NVIDIA_2_APBASE, apbase, 4);
	pci_write_config(sc->mc2_dev, AGP_NVIDIA_2_APLIMIT, aplimit, 4);
	pci_write_config(sc->bdev, AGP_NVIDIA_3_APBASE, apbase, 4);
	pci_write_config(sc->bdev, AGP_NVIDIA_3_APLIMIT, aplimit, 4);

	error = nvidia_init_iorr(apbase, AGP_GET_APERTURE(dev));
	if (error) {
		device_printf(dev, "Failed to setup IORRs\n");
		goto fail;
	}

	/* directory size is 64k */
	size = AGP_GET_APERTURE(dev) / 1024 / 1024;
	sc->num_dirs = size / 64;
	sc->num_active_entries = (size == 32) ? 16384 : ((size * 1024) / 4);
	sc->pg_offset = 0;
	if (sc->num_dirs == 0) {
		sc->num_dirs = 1;
		sc->num_active_entries /= (64 / size);
		sc->pg_offset = rounddown2(apbase & (64 * 1024 * 1024 - 1),
		    AGP_GET_APERTURE(dev)) / PAGE_SIZE;
	}

	/* (G)ATT Base Address */
	for (i = 0; i < 8; i++) {
		pci_write_config(sc->mc2_dev, AGP_NVIDIA_2_ATTBASE(i),
				 (sc->gatt->ag_physical +
				   (i % sc->num_dirs) * 64 * 1024) | 1, 4);
	}

	/* GTLB Control */
	temp = pci_read_config(sc->mc2_dev, AGP_NVIDIA_2_GARTCTRL, 4);
	pci_write_config(sc->mc2_dev, AGP_NVIDIA_2_GARTCTRL, temp | 0x11, 4);

	/* GART Control */
	temp = pci_read_config(sc->dev, AGP_NVIDIA_0_APSIZE, 4);
	pci_write_config(sc->dev, AGP_NVIDIA_0_APSIZE, temp | 0x100, 4);

	return (0);
fail:
	agp_generic_detach(dev);
	return (ENOMEM);
}