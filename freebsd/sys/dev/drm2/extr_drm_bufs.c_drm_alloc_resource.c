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
struct resource {int dummy; } ;
struct drm_device {int* pcirid; struct resource** pcir; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int DRM_MAX_PCI_RESOURCE ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_alloc_resource(struct drm_device *dev, int resource)
{
	struct resource *res;
	int rid;

	if (resource >= DRM_MAX_PCI_RESOURCE) {
		DRM_ERROR("Resource %d too large\n", resource);
		return 1;
	}

	if (dev->pcir[resource] != NULL) {
		return 0;
	}

	rid = PCIR_BAR(resource);
	res = bus_alloc_resource_any(dev->dev, SYS_RES_MEMORY, &rid,
	    RF_SHAREABLE);
	if (res == NULL) {
		DRM_ERROR("Couldn't find resource 0x%x\n", resource);
		return 1;
	}

	if (dev->pcir[resource] == NULL) {
		dev->pcirid[resource] = rid;
		dev->pcir[resource] = res;
	}

	return 0;
}