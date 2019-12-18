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
struct vdevice_devinfo {int /*<<< orphan*/ * mdi_dma_tag; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ *) ; 
 struct vdevice_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phyp_iommu_set_dma_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bus_dma_tag_t
vdevice_get_dma_tag(device_t dev, device_t child)
{
	struct vdevice_devinfo *dinfo;
	while (child != NULL && device_get_parent(child) != dev)
		child = device_get_parent(child);
        dinfo = device_get_ivars(child);

	if (dinfo->mdi_dma_tag == NULL) {
		bus_dma_tag_create(bus_get_dma_tag(dev),
		    1, 0, BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR,
		    NULL, NULL, BUS_SPACE_MAXSIZE, BUS_SPACE_UNRESTRICTED,
		    BUS_SPACE_MAXSIZE, 0, NULL, NULL, &dinfo->mdi_dma_tag);
		phyp_iommu_set_dma_tag(dev, child, dinfo->mdi_dma_tag);
	}

        return (dinfo->mdi_dma_tag);
}