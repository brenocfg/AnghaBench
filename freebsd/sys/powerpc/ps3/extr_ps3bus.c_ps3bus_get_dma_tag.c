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
struct ps3bus_softc {int rcount; TYPE_1__* regions; } ;
struct ps3bus_devinfo {scalar_t__ bustype; scalar_t__ devtype; int /*<<< orphan*/ * dma_tag; int /*<<< orphan*/  iommu_mtx; int /*<<< orphan*/ * dma_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;
struct TYPE_2__ {int /*<<< orphan*/  mr_size; int /*<<< orphan*/  mr_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE ; 
 scalar_t__ PS3_BUSTYPE_STORAGE ; 
 scalar_t__ PS3_BUSTYPE_SYSBUS ; 
 scalar_t__ PS3_DEVTYPE_USB ; 
 int bus_dma_tag_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dma_tag_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ps3bus_devinfo*) ; 
 int /*<<< orphan*/ * bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct ps3bus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ps3bus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int lv1_allocate_device_dma_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int lv1_map_device_dma_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bus_dma_tag_t
ps3bus_get_dma_tag(device_t dev, device_t child)
{
	struct ps3bus_devinfo *dinfo = device_get_ivars(child);
	struct ps3bus_softc *sc = device_get_softc(dev);
	int i, err, flags, pagesize;

	if (dinfo->bustype != PS3_BUSTYPE_SYSBUS &&
	    dinfo->bustype != PS3_BUSTYPE_STORAGE)
		return (bus_get_dma_tag(dev));

	mtx_lock(&dinfo->iommu_mtx);
	if (dinfo->dma_tag != NULL) {
		mtx_unlock(&dinfo->iommu_mtx);
		return (dinfo->dma_tag);
	}

	flags = 0; /* 32-bit mode */
	if (dinfo->bustype == PS3_BUSTYPE_SYSBUS &&
	    dinfo->devtype == PS3_DEVTYPE_USB)
		flags = 2; /* 8-bit mode */

	pagesize = 24; /* log_2(16 MB) */
	if (dinfo->bustype == PS3_BUSTYPE_STORAGE)
		pagesize = 12; /* 4 KB */

	for (i = 0; i < sc->rcount; i++) {
		err = lv1_allocate_device_dma_region(dinfo->bus, dinfo->dev,
		    sc->regions[i].mr_size, pagesize, flags,
		    &dinfo->dma_base[i]);
		if (err != 0) {
			device_printf(child,
			    "could not allocate DMA region %d: %d\n", i, err);
			goto fail;
		}

		err = lv1_map_device_dma_region(dinfo->bus, dinfo->dev,
		    sc->regions[i].mr_start, dinfo->dma_base[i],
		    sc->regions[i].mr_size,
		    0xf800000000000800UL /* Cell Handbook Figure 7.3.4.1 */);
		if (err != 0) {
			device_printf(child,
			    "could not map DMA region %d: %d\n", i, err);
			goto fail;
		}
	}

	err = bus_dma_tag_create(bus_get_dma_tag(dev),
	    1, 0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
	    NULL, NULL, BUS_SPACE_MAXSIZE, 0, BUS_SPACE_MAXSIZE,
	    0, NULL, NULL, &dinfo->dma_tag);

	/*
	 * Note: storage devices have IOMMU mappings set up by the hypervisor,
	 * but use physical, non-translated addresses. The above IOMMU
	 * initialization is necessary for the hypervisor to be able to set up
	 * the mappings, but actual DMA mappings should not use the IOMMU
	 * routines.
	 */
	if (dinfo->bustype != PS3_BUSTYPE_STORAGE)
		bus_dma_tag_set_iommu(dinfo->dma_tag, dev, dinfo);

fail:
	mtx_unlock(&dinfo->iommu_mtx);

	if (err)
		return (NULL);

	return (dinfo->dma_tag);
}