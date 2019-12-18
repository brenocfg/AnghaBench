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
struct drm_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ ** pcir; int /*<<< orphan*/ * pcirid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_MAX_PCI_RESOURCE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_device* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_put_dev (struct drm_device*) ; 
 scalar_t__ pci_disable_busmaster (int /*<<< orphan*/ ) ; 

int
drm_generic_detach(device_t kdev)
{
	struct drm_device *dev;
	int i;

	dev = device_get_softc(kdev);

	drm_put_dev(dev);

	/* Clean up PCI resources allocated by drm_bufs.c.  We're not really
	 * worried about resource consumption while the DRM is inactive (between
	 * lastclose and firstopen or unload) because these aren't actually
	 * taking up KVA, just keeping the PCI resource allocated.
	 */
	for (i = 0; i < DRM_MAX_PCI_RESOURCE; i++) {
		if (dev->pcir[i] == NULL)
			continue;
		bus_release_resource(dev->dev, SYS_RES_MEMORY,
		    dev->pcirid[i], dev->pcir[i]);
		dev->pcir[i] = NULL;
	}

	if (pci_disable_busmaster(dev->dev))
		DRM_ERROR("Request to disable bus-master failed.\n");

	return (0);
}