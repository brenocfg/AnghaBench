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
struct drm_device {scalar_t__ irqrid; scalar_t__ msi_enabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

void
drm_pci_disable_msi(struct drm_device *dev)
{

	if (!dev->msi_enabled)
		return;

	pci_release_msi(dev->dev);
	dev->msi_enabled = 0;
	dev->irqrid = 0;
}