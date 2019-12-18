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
struct drm_device {int irq; scalar_t__ irqr; int /*<<< orphan*/  dev; int /*<<< orphan*/  irqrid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rman_get_start (scalar_t__) ; 

__attribute__((used)) static int drm_pci_get_irq(struct drm_device *dev)
{

	if (dev->irqr)
		return (dev->irq);

	dev->irqr = bus_alloc_resource_any(dev->dev, SYS_RES_IRQ,
	    &dev->irqrid, RF_SHAREABLE);
	if (!dev->irqr) {
		dev_err(dev->dev, "Failed to allocate IRQ\n");
		return (0);
	}

	dev->irq = (int) rman_get_start(dev->irqr);

	return (dev->irq);
}