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
struct drm_device {int msi_enabled; int irqrid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  drm_msi ; 
 int pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 

int
drm_pci_enable_msi(struct drm_device *dev)
{
	int msicount, ret;

	if (!drm_msi)
		return (-ENOENT);

	msicount = pci_msi_count(dev->dev);
	DRM_DEBUG("MSI count = %d\n", msicount);
	if (msicount > 1)
		msicount = 1;

	ret = pci_alloc_msi(dev->dev, &msicount);
	if (ret == 0) {
		DRM_INFO("MSI enabled %d message(s)\n", msicount);
		dev->msi_enabled = 1;
		dev->irqrid = 1;
	}

	return (-ret);
}